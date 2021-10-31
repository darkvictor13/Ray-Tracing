#ifndef RAY
#define RAY

#include "../vector_3d/vector_3d.hpp"

struct Ray {
	Point3d origin;
	Vector3d direction;

	Ray();
	Ray(Point3d origin, Vector3d direction);

	Point3d at(double t) const;
};


#endif // RAY
