#ifndef SPHERE_MOVING
#define SPHERE_MOVING

#include "sphere_base.hpp"

class SphereMoving : public Hittable, public SphereBase {
private:
	Point3d center_at_t0, center_at_t1;
	double time_0, time_1;

	Point3d calculateCenter(const double time) const;

public:
	SphereMoving();
	SphereMoving(const Point3d &c0, const Point3d &c1, double t0, double t1, double radius, std::shared_ptr<Material> m);

	virtual bool hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const override;

	~SphereMoving();
};


#endif //SPHERE_MOVING