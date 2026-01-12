#include "hamster/config.hpp"
#include "utils/utils.hpp"
#include <fstream>
#include <sstream>

namespace Hamster
{

auto Config::Trim(const std::string &s) -> std::string
{
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

auto Config::ParseConfig(const std::string &filename) -> Cfg
{
    Cfg cfg{};
    std::ifstream file(filename);
    if (!file.is_open())
        return cfg;

    enum class BlockType { None, Step, Build, Entry };

    BlockType currentType = BlockType::None;
    std::vector<std::string>* currentCmds = nullptr;

    std::string line;
    while (std::getline(file, line))
    {
        line = Trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        if (line == "}")
        {
            currentType = BlockType::None;
            currentCmds = nullptr;
            continue;
        }

        auto eqPos = line.find('=');
        if (currentType == BlockType::None && eqPos != std::string::npos)
        {
            auto key = Trim(line.substr(0, eqPos));
            auto value = Trim(line.substr(eqPos + 1));
            cfg.variables[key] = value;
            continue;
        }

        if (line.rfind("step ", 0) == 0)
        {
            auto name = Trim(line.substr(5));
            if (!name.empty() && name.back() == '{')
                name.pop_back();

            Step step{};
            step.name = Trim(name);
            cfg.steps[step.name] = step;

            currentType = BlockType::Step;
            currentCmds = &cfg.steps[step.name].cmds;
            continue;
        }

        if (line.rfind("build ", 0) == 0)
        {
            auto name = Trim(line.substr(6));
            if (!name.empty() && name.back() == '{')
                name.pop_back();

            Build build{};
            build.name = Trim(name);
            cfg.builds[build.name] = build;

            currentType = BlockType::Build;
            currentCmds = &cfg.builds[build.name].cmds;
            continue;
        }

        if (line.rfind("entry ", 0) == 0)
        {
            if (!cfg.entrypoint.empty())
            {
                continue;
            }

            auto name = Trim(line.substr(6));
            if (!name.empty() && name.back() == '{')
                name.pop_back();

            currentType = BlockType::Entry;
            currentCmds = &cfg.entrypoint;
            continue;
        }

        if (line == "{")
            continue;

        if (currentCmds)
        {
            currentCmds->push_back(line);
        }
    }

    return cfg;
}

auto Config::MakeConfig() -> bool
{
    auto config = R"(# variables

compiler = g++;
linker = g++;

warnings = -Wall;
compiler_args = -O2;

src_dir = src/;
include_dir = include/;
bin_dir = bin/;
output = myprogram;

# steps

step compile
{
    compile src_dir into bin_dir
        with compiler_args, warnings, include_dir;
}

step link
{
    link all objects in bin_dir
        into output;
}

step run_scripts
{
    run scripts/script1.sh;
    run scripts/script2.sh;
}

build default
{
    run compile;
    run link;
}

# entrypoint

entry main
{
    run default;
    run run_scripts;

    if "run" in args
    {
        print("running");
        run_cmd "./myprogram";
    }
}
)";

    std::ofstream out("hamster.conf");
    if (!out)
    {
        LogError("Failed to create config");
        return false;
    }

    out << config;
    out.close();

    return true;
}

}
