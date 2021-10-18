#include "color.hpp"

void writeColor(std::ostream &out, Color pixel) {
    out << static_cast<int>(255.999 * pixel.red())   << ' '
        << static_cast<int>(255.999 * pixel.green()) << ' '
        << static_cast<int>(255.999 * pixel.blue())  << '\n';
}