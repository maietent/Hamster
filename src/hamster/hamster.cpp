#include "hamster/hamster.hpp"
#include "utils/utils.hpp"

namespace Hamster
{

Hamster::Hamster(const std::vector<std::string>& args)
{
    Log("Constructor called");
    if (!Initialize(args))
    {
        throw std::runtime_error("Hamster failed to initialize");
    }
}

Hamster::~Hamster()
{
    Log("Deconstructor called");
    Deinitialize();
}

auto Hamster::ParseArgs(const std::vector<std::string>& args) -> bool
{
    if (args.empty())
    {
        LogError("No arguments passed, continuing");
        return true;
    }

    // this can 100% be done better

    // if it starts with - then its an arg for the app itself
    // if it doesnt, its an arg for the building
    for (const auto& arg : args)
    {
        if (arg.empty())
            continue;

        if (arg[0] == '-')
        {
            if (arg == "-make")
                Log("TODO: autogen conf file and prompt user", arg);
            else
            {
                LogError("Unknown argument: {}", arg);
                return false;
            }
        }
        else
        {
            Log("Build argument: {}", arg);
            BuildArgs.push_back(arg);
        }
    }

    return true;
}

auto Hamster::Initialize(const std::vector<std::string>& args) -> bool
{
    Log("Initialize called");

    if (!ParseArgs(args))
    {
        LogError("Failed to parse arguments");
        return false;
    }

    Cfg cfg = config_inst.ParseConfig("hamster.conf");
    if (cfg.variables.empty() && cfg.steps.empty() && cfg.entry_commands.empty())
    {
        LogError("Failed to parse hamster.conf");
        return false;
    }

    return true;
}


auto Hamster::Deinitialize() -> void
{
    Log("Deinitialize called");
}

}
