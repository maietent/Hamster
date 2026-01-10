#include "hamster/hamster.hpp"
#include "utils/log.hpp"

namespace Hamster
{

Hamster::Hamster()
{
    log("Constructor called");
    if (!Initialize())
    {
        throw std::runtime_error("Hamster failed to initialize");
    }
}

Hamster::~Hamster()
{
    log("Deconstructor called");
    Deinitialize();
}

auto Hamster::Initialize()   -> bool
{
    log("Initialize called");
    return true;
}

auto Hamster::Deinitialize() -> void
{
    log("Deinitialize called");
}

}
