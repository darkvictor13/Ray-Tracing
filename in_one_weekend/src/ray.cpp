#include "ray.hpp"

Point3d Ray::at(double t) const {
    return origin + t * direction;
}

Ray::Ray() : origin(), direction() {}

Ray::Ray(Point3d origin, Vector3d direction)
: origin(origin), direction(direction) {}
