#ifndef NUMBERS
#define NUMBERS

#include <limits>
#include <cstdlib>
#include <cmath>

#define INF std::numeric_limits<double>::infinity()

namespace utils {
	double randomDouble();
	double randomDouble(double min, double max);
    double degreesToRadians(double rad);
}

#endif // NUMBERS
