#include "ppm_writer.hpp"
#include <cmath>

PpmWriter::PpmWriter(const std::string &temp, int height, int width,
        int samples_per_pixel) : file_buffer(temp),
        _height(height), _width(width), _samples_per_pixel(samples_per_pixel) {}

void PpmWriter::writeHeader() {
    file_buffer << "P3\n" << _width << ' ' << _height << "\n255\n";
}

void PpmWriter::writeColor(Color color) {
	double red = color.red;
	double green = color.green;
	double blue = color.blue;

	double scale = 1.0 / _samples_per_pixel;
    red = std::sqrt(scale * red);
    green = std::sqrt(scale * green);
    blue = std::sqrt(scale * blue);

    file_buffer << static_cast<int>(256 * std::clamp(red, 0.0, 0.999))   << ' '
        		<< static_cast<int>(256 * std::clamp(green, 0.0, 0.999)) << ' '
        		<< static_cast<int>(256 * std::clamp(blue, 0.0, 0.999))  << '\n';
}

void PpmWriter::writeImage(const Color image[][IMAGE_WIDTH]) {
    int i, j;
    for (i = 0; i < _height; i++) {
        for (j = 0; j < _width; j++) {
            writeColor(image[i][j]);
        }
    }
}

PpmWriter::~PpmWriter() {
	file_buffer.close();
}
