#include "numbers.hpp"

double utils::randomDouble() {
	return rand() / (RAND_MAX + 1.0);
}

double utils::randomDouble(double min, double max) {
	return min + (max-min)*randomDouble();
}

double utils::degreesToRadians(double rad) {
    return rad * M_PI / 180.0;
}

