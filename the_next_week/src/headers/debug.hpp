#ifndef DEBUG
#define DEBUG

#include "user_config.hpp"

#if DEBUG_VAR
	#define debug(x) std::cout << x
#else
	#define debug(x)
#endif

#endif // DEBUG
