#include "ppm_writer.hpp"

ColorRep::ColorRep() : r(), g(), b() {}

ColorRep::ColorRep(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

ColorRep::ColorRep(const Color color) {
    *this = color;
}

std::ostream& operator << (std::ostream &out, const ColorRep &c) {
    return out << static_cast<uint16_t>(c.r) << ' ' <<
        static_cast<uint16_t>(c.g) << ' ' <<
        static_cast<uint16_t>(c.b) << '\n';
}

void ColorRep::operator = (const Color &color) {
    double red = color.red;
    double green = color.green;
    double blue = color.blue;
    double scale = 1.0 / SAMPLES_PER_PIXEL;

    red = std::sqrt(scale * red);
    green = std::sqrt(scale * green);
    blue = std::sqrt(scale * blue);

    r = (256 * std::clamp(red, 0.0, 0.999));
    g = (256 * std::clamp(green, 0.0, 0.999));
    b = (256 * std::clamp(blue, 0.0, 0.999));
}

PpmWriter::PpmWriter(const std::string &temp, int height, int width,
        int samples_per_pixel) : file_buffer(temp, std::ios::out | std::ios::binary),
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

void PpmWriter::writeImage(const ColorRep image[][IMAGE_WIDTH]) {
    int i, j;
    for (i = 0; i < _height; i++) {
        for (j = 0; j < _width; j++) {
            file_buffer << image[i][j];
        }
    }
}

PpmWriter::~PpmWriter() {
	file_buffer.close();
}
