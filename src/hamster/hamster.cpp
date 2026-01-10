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
        LogError("No arguments passed");
        return false;
    }

    // this can 100% be done better
    size_t index = 0;
    for (const auto& arg : args)
    {
        index++;

        if (arg == "-a")
        {
            Log("-a passed");
        }
        else if (arg == "-b")
        {
            Log("-b passed");
        }

        else if (arg == "-c")
        {
            Log("-c passed");
        }
        else
        {
            LogError("Unknown argument: {}", arg);
            return false;
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

    return true;
}

auto Hamster::Deinitialize() -> void
{
    Log("Deinitialize called");
}

}
