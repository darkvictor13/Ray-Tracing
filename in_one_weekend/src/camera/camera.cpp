#include "camera.hpp"

Camera::Camera() : origin(0, 0, 0), horizontal(VIEWPORT_WIDTH, 0, 0), vertical(0, VIEWPORT_HEIGHT, 0),
	lower_left_corner(origin - horizontal/2 - vertical/2 - Vector3d(0, 0, FOCAL_LENGTH)) {}

Ray Camera::getRay(double u, double v) const {
    return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}

Camera::~Camera() {}