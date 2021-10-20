#ifndef NUMBERS
#define NUMBERS

#include <limits>
#include <cstdlib>

namespace utils {
	const double INF = std::numeric_limits<double>::infinity();

	double randomDouble();
	double randomDouble(double min, double max);
}

#endif // NUMBERS
