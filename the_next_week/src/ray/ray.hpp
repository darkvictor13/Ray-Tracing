#ifndef RAY
#define RAY

#include "../vector_3d/vector_3d.hpp"

struct Ray {
	Point3d origin;
	Vector3d direction;
	double time;

	Ray();
	Ray(const Point3d &origin, const Vector3d &direction, const double time = 0.0);

	Point3d at(double t) const;
};


#endif // RAY
