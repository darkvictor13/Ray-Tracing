#ifndef CAMERA
#define CAMERA

#include "../headers/debug.hpp"
#include "../vector_3d/vector_3d.hpp"
#include "../ray/ray.hpp"

#define VIEWPORT_HEIGHT 2.0
#define VIEWPORT_WIDTH  (ASPECT_RATIO * VIEWPORT_HEIGHT)
#define FOCAL_LENGTH    1.0

class Camera {
private:
    Point3d origin;
    Vector3d horizontal;
    Vector3d vertical;
    Vector3d lower_left_corner;
public:
	Camera();

	Ray getRay(double u, double v) const;

	~Camera();
};

#endif // CAMERA
