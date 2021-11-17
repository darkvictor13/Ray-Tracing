#ifndef SCOPE_TIMER
#define SCOPE_TIMER

#include "../pch/std.hpp"
#include "../headers/debug.hpp"

class ScopeTimer {
private:
    std::string scope_name;
    bool print_in_seconds;
    std::chrono::high_resolution_clock::time_point start;
public:
    ScopeTimer(std::string scope_name,
            bool print_in_seconds = true);
    ~ScopeTimer();
};

#endif // SCOPE_TIMER
