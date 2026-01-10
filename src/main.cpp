#include "hamster/hamster.hpp"

auto main(int argc, char* argv[]) -> int
{
    std::vector<std::string> args(argv + 1, argv + argc); // arguments!

    Hamster::Hamster app{args};
    return 0;
}
