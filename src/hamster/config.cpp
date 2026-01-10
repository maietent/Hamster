#include "hamster/config.hpp"
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
    auto cfg = Cfg{};
    auto file = std::ifstream(filename);
    if (!file.is_open())
    {
        return cfg;
    }

    auto line = std::string{};
    Step* currentStep = nullptr;
    auto inEntry = false;

    while (std::getline(file, line))
    {
        line = Trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto eqPos = line.find('=');
        if (eqPos != std::string::npos && !inEntry && line.rfind("Step:", 0) != 0)
        {
            auto key = Trim(line.substr(0, eqPos));
            auto value = Trim(line.substr(eqPos + 1));
            cfg.variables[key] = value;
            continue;
        }

        if (line.rfind("Step:", 0) == 0)
        {
            auto stepName = Trim(line.substr(5));
            auto step = Step{};
            step.name = stepName;
            cfg.steps[stepName] = step;
            currentStep = &cfg.steps[stepName];
            inEntry = false;
            continue;
        }

        if (line.rfind("Entry", 0) == 0)
        {
            inEntry = true;
            currentStep = nullptr;
            continue;
        }

        if (line == "{" || line == "}") continue;

        if (currentStep)
        {
            currentStep->cmds.push_back(line);
        }
        else if (inEntry)
        {
            cfg.entry_commands.push_back(line);
        }
    }

    return cfg;
}

}
