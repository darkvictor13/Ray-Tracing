#include "sphere_moving.hpp"


Point3d SphereMoving::calculateCenter(const double time) const {
	return center_at_t0 +
		   ((time - time_0) / (time_1 - time_0)) * (center_at_t1 - center_at_t0);
}

SphereMoving::SphereMoving(const Point3d &c0, const Point3d &c1,
						double t0, double t1, double radius,
						std::shared_ptr<Material> m) :
						SphereBase(radius, m),
						center_at_t0(c0), center_at_t1(c1),
						time_0(t0), time_1(t1) {
}

bool SphereMoving::hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const {

	return sphereHit(r, t_min, t_max, rec, calculateCenter(r.time));
}

SphereMoving::~SphereMoving() {
    
}
