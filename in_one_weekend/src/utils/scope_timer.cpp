#include "scope_timer.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

ScopeTimer::ScopeTimer(std::string scope_name, bool in_seconds) :
    scope_name(scope_name),
    print_in_seconds(in_seconds),
    start(high_resolution_clock::now()) {
}

ScopeTimer::~ScopeTimer() {
    const auto elapsed_time = high_resolution_clock::now() - start;

    debug (scope_name << " executou por: ");
    if (print_in_seconds) {
        debug (
            static_cast<duration<double>>(elapsed_time).count() << ' ');
    }else {
        debug (elapsed_time.count() << " nano");
    }
    debug ("segundos\n");
}
