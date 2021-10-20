#include "ppm_writer.hpp"

PpmWriter::PpmWriter(const std::string &temp, int height, int width,
        int samples_per_pixel) :
        file_buffer(temp), height(height), width(width),
        samples_per_pixel(samples_per_pixel) {}

void PpmWriter::writeHeader() {
    file_buffer << "P3\n" << this->width << ' '
                << this->height << "\n255\n";
}

void PpmWriter::writeColor(Color color) {
	double red = color.red();
	double green = color.green();
	double blue = color.blue();

	double scale = 1.0 / samples_per_pixel;
    red *= scale;
    green *= scale;
    blue *= scale;

    file_buffer << static_cast<int>(256 * std::clamp(red, 0.0, 0.999))   << ' '
        		<< static_cast<int>(256 * std::clamp(green, 0.0, 0.999)) << ' '
        		<< static_cast<int>(256 * std::clamp(blue, 0.0, 0.999))  << '\n';
}

// TODO
void PpmWriter::writeImage() {
    int i, j;
    for (j = height - 1; j >= 0; j--) {
        std::cout << "Faltam " << std::setfill('0') << std::setw(3) << j << " linhas para gerar\n";
        for (i = 0; i < width; i++) {
            Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++) {
            }
			writeColor(pixel_color);
        }
    }
}

PpmWriter::~PpmWriter() {
	file_buffer.close();
}
