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
        const duration<double> to_sec = elapsed_time;
        const double sec = to_sec.count();
        const double min = sec / 60;
        debug (min << "minutos e " << sec << ' ');
    }else {
        debug (elapsed_time.count() << " nano");
    }
    debug ("segundos\n");
}
