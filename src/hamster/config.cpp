#include "hamster/config.hpp"
#include <fstream>
#include <sstream>

namespace Hamster
{

auto Config::Trim(const std::string &s) -> std::string
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

auto Config::ParseConfig(const std::string &filename) -> Cfg
{
    Cfg cfg;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        return cfg;
    }

    std::string line;
    Step* currentStep = nullptr;
    bool inEntry = false;

    while (std::getline(file, line))
    {
        line = Trim(line);
        if (line.empty() || line[0] == '#') continue;

        size_t eqPos = line.find('=');
        if (eqPos != std::string::npos && !inEntry && line.rfind("Step:", 0) != 0)
        {
            std::string key = Trim(line.substr(0, eqPos));
            std::string value = Trim(line.substr(eqPos + 1));
            cfg.variables[key] = value;
            continue;
        }

        if (line.rfind("Step:", 0) == 0)
        {
            std::string stepName = Trim(line.substr(5));
            Step step;
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
