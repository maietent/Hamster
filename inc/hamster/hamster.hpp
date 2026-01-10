#pragma once

namespace Hamster
{

class Hamster
{
public:
    Hamster();
    ~Hamster();
private:
    auto Initialize()   -> bool;
    auto Deinitialize() -> void;
};

}
