#ifndef SETUP
#define SETUP

#define IMAGE_PATH        "../images/"
#define DEFAULT_FILE_NAME "bola.ppm"

// Imagem
#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH  400
#define IMAGE_HEIGHT static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO)
#define SAMPLES_PER_PIXEL 100

// Câmera
#define VIEWPORT_HEIGHT 2.0
#define VIEWPORT_WIDTH  (ASPECT_RATIO * VIEWPORT_HEIGHT)
#define FOCAL_LENGTH    1.0

#endif // SETUP
