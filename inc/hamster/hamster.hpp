#pragma once

#include "hamster/config.hpp"

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
    auto ParseArgs(const std::vector<std::string>& args) -> bool;
    auto Initialize(const std::vector<std::string>& args) -> bool;
    auto Deinitialize() -> void;
private:
    std::vector<std::string> BuildArgs;
    auto GetBuildArgs() const -> const std::vector<std::string>& { return BuildArgs; }
private:
    Config config_inst{};
};

}
