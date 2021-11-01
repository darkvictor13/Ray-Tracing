#ifndef SPHERE
#define SPHERE

#include "hittable.hpp"
#include <memory>

struct Sphere : public Hittable {
	Point3d center;
	double radius;
    std::shared_ptr<Material> material;

	Sphere();
	Sphere(Point3d center, double radius, std::shared_ptr<Material> m);
	virtual bool hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const override;
};


#endif // SPHERE
