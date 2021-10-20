#ifndef CAMERA
#define CAMERA

#include "setup.hpp"
#include "../vector/vector.hpp"
#include "../ray/ray.hpp"

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
