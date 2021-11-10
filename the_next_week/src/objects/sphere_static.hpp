#ifndef SPHERE_STATIC
#define SPHERE_STATIC

#include "sphere_base.hpp"

class SphereStatic : public Hittable, public SphereBase {
private:
	Point3d center;

public:
	SphereStatic();
	SphereStatic(const Point3d &center, double radius, std::shared_ptr<Material> m);

	virtual bool hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const override;

	~SphereStatic();
};


#endif // SPHERE_STATIC
