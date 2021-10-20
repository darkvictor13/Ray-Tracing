#ifndef SPHERE
#define SPHERE

#include "hittable.hpp"

struct Sphere : public Hittable {
	Point3d center;
	double radius;

	Sphere();
	Sphere(Point3d center, double radius);
	virtual bool hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const override;
};


#endif // SPHERE
