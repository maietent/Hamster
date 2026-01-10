#pragma once

#include <vector>
#include <string>

namespace Hamster
{

class Hamster
{
public:
    Hamster(const std::vector<std::string>& args);
    ~Hamster();
private:
    auto Initialize(const std::vector<std::string>& args) -> bool;
    auto Deinitialize() -> void;
};

}
