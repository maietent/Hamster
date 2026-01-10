#include "hamster/hamster.hpp"

Hamster::Hamster()
{
    std::println("Constructor called");
    if (!Initialize())
    {
        throw std::runtime_error("Hamster failed to initialize");
    }
}

Hamster::~Hamster()
{
    std::println("Deconstructor called");
    Deinitialize();
}

bool Hamster::Initialize()
{
    std::println("Initialize called");
    return true;
}

void Hamster::Deinitialize()
{
    std::println("Deinitialize called");
}
