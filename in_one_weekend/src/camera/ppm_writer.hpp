#ifndef PPM_WRITER
#define PPM_WRITER

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "setup.hpp"
#include "../vector/vector.hpp"
#include "../utils/numbers.hpp"
#include "../ray/ray.hpp"

class PpmWriter {
private:
	std::ofstream file_buffer;
	int height, width, samples_per_pixel;
public:
	PpmWriter(const std::string &temp = (std::string(IMAGE_PATH) + DEFAULT_FILE_NAME),
				int height = IMAGE_HEIGHT,
				int width  = IMAGE_WIDTH,
				int samples_per_pixel = SAMPLES_PER_PIXEL);

	void writeColor(Color color);
	void writeHeader();
	void writeImage(const Color image[IMAGE_WIDTH][IMAGE_HEIGHT]);
	~PpmWriter();
};

#endif // PPM_WRITER
