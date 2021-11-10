#ifndef SPHERE_BASE
#define SPHERE_BASE

#include "hittable.hpp"

class SphereBase {
protected:
	double radius;
    std::shared_ptr<Material> material;

	bool sphereHit(const Ray& r, double t_min, double t_max,
					HitRecord& rec, const Point3d &center) const;
public:
	SphereBase();
	SphereBase(double radius, std::shared_ptr<Material> material);

	~SphereBase();
};


#endif // SPHERE_BASE