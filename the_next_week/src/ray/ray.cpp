#include "ray.hpp"

Point3d Ray::at(double t) const {
    return origin + t * direction;
}

Ray::Ray() : origin(), direction() {}

Ray::Ray(const Point3d &origin, const Vector3d &direction, const double time)
: origin(origin), direction(direction), time(time) {}
