#ifndef PPM_WRITER
#define PPM_WRITER

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "setup.hpp"
#include "../vector_3d/vector_3d.hpp"
#include "../utils/numbers.hpp"
#include "../ray/ray.hpp"

class PpmWriter {
private:
	std::ofstream file_buffer;
	int _height, _width, _samples_per_pixel;
public:
	PpmWriter(const std::string &temp = (std::string(IMAGE_PATH) + DEFAULT_FILE_NAME),
				int _height = IMAGE_HEIGHT,
				int _width  = IMAGE_WIDTH,
				int _samples_per_pixel = SAMPLES_PER_PIXEL);

	void writeColor(Color color);
	void writeHeader();
	void writeImage(const Color image[][IMAGE_WIDTH]);
	~PpmWriter();
};

#endif // PPM_WRITER
