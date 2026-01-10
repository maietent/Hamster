#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Hamster
{

struct Step
{
    std::string name;
    std::vector<std::string> cmds;
};

struct Cfg
{
    std::unordered_map<std::string, std::string> variables;
    std::unordered_map<std::string, Step> steps;
    std::vector<std::string> entry_commands;
    std::vector<std::string> args;
};

class Config
{
public:
    auto ParseConfig(const std::string &filename) -> Cfg;
private:
    auto Trim(const std::string &s) -> std::string;
};

}
