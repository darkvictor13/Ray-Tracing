#include "color.hpp"

void writeColor(std::ostream &out, Color pixel, int samples_per_pixel) {
	double red = pixel.red();
	double green = pixel.green();
	double blue = pixel.blue();

	auto scale = 1.0 / samples_per_pixel;
    red *= scale;
    green *= scale;
    blue *= scale;

    out << static_cast<int>(256 * std::clamp(red, 0.0, 0.999))   << ' '
        << static_cast<int>(256 * std::clamp(green, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(blue, 0.0, 0.999))  << '\n';
}