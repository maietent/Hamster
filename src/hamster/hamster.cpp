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

auto Hamster::Initialize(const std::vector<std::string>& args) -> bool
{
    Log("Initialize called");

    if (args.empty())
    {
        Log("No arguments passed");
        return false;
    }

    size_t index = 0;
    for (const auto& arg : args)
    {
        Log("{}: {}", index++, arg);
    }


    return true;
}

auto Hamster::Deinitialize() -> void
{
    Log("Deinitialize called");
}

}
