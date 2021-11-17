#ifndef PPM_WRITER
#define PPM_WRITER

#include "../pch/std.hpp"

#include "../headers/debug.hpp"
#include "../vector_3d/vector_3d.hpp"
#include "../utils/numbers.hpp"
#include "../ray/ray.hpp"

#define IMAGE_HEIGHT static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO)
#define SAMPLES_PER_PIXEL 100

struct ColorRep {
    uint8_t r, g, b;

    ColorRep();
    ColorRep(uint8_t r, uint8_t g, uint8_t b);
    ColorRep(const Color color);

    friend std::ostream& operator << (std::ostream &out, const ColorRep &c);

    void operator = (const Color &color);
};

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
    void writeImage(const ColorRep image[][IMAGE_WIDTH]);
    ~PpmWriter();
};

#endif // PPM_WRITER
