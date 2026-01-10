#pragma once

#include <print>
#include <source_location>

template <typename... Args>
inline auto log(std::format_string<Args...> fmt,
                const std::source_location& loc = std::source_location::current(),
                Args&&... args) -> void
{
    std::print("[{}:{} | {}] ", loc.file_name(), loc.line(), loc.function_name());
    std::print(fmt, std::forward<Args>(args)...);
    std::print("\n");
}
