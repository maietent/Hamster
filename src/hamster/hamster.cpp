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
            {
                config_inst.MakeConfig();
                Log("Created default config");
            }
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
    if (cfg.variables.empty() && cfg.steps.empty() && cfg.builds.empty() && cfg.entrypoint.empty())
    {
        LogError("Failed to parse hamster.conf");
        return false;
    }

    Log("Variables:");
    for (const auto& [key, value] : cfg.variables)
    {
        Log("  {} = {}", key.c_str(), value.c_str());
    }

    Log("Steps:");
    for (const auto& [name, step] : cfg.steps)
    {
        Log("  step {}", name.c_str());
        for (const auto& cmd : step.cmds)
        {
            Log("    {}", cmd.c_str());
        }
    }

    Log("Builds:");
    for (const auto& [name, build] : cfg.builds)
    {
        Log("  build {}", name.c_str());
        for (const auto& cmd : build.cmds)
        {
            Log("    {}", cmd.c_str());
        }
    }

    Log("Entrypoint:");
    for (const auto& cmd : cfg.entrypoint)
    {
        Log("    {}", cmd.c_str());
    }

    return true;
}


auto Hamster::Deinitialize() -> void
{
    Log("Deinitialize called");
}

}
