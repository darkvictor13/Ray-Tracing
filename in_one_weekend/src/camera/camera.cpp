#include "camera.hpp"

Camera::Camera(double fov,
        const Vector3d &up,
        const Point3d &look_at,
        const Point3d &look_from) {

    double h = tan(utils::degreesToRadians(fov) / 2);
    double viewport_height = 2.0 * h;
    double viewport_width = ASPECT_RATIO * viewport_height;

    Vector3d w = unitVector(look_from - look_at);
    Vector3d u = unitVector(cross(up, w));
    Vector3d v = cross(w, u);

    origin = look_from;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal/2 - vertical/2 - w;
}

Ray Camera::getRay(double u, double v) const {
    return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}

Camera::~Camera() {}
