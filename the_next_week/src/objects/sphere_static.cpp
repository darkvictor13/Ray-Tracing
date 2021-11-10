#include "sphere_static.hpp"

SphereStatic::SphereStatic() : SphereBase(), center() {
}

SphereStatic::SphereStatic(const Point3d &center, double radius, std::shared_ptr<Material> m) :
							SphereBase(radius, m), center(center) {
}

bool SphereStatic::hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const {

	return sphereHit(r, t_min, t_max, rec, center);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
bool SphereStatic::boundingBox(double initial_time,
			double final_time, Aabb &out_box) const {

	const Vector3d limits(radius, radius, radius);
	out_box = Aabb(center - limits, center + limits);
	return true;
}
#pragma GCC diagnostic pop

SphereStatic::~SphereStatic() {
}