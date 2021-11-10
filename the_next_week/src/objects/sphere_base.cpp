#include "sphere_base.hpp"

SphereBase::SphereBase() : radius() {
}

SphereBase::SphereBase(double radius, std::shared_ptr<Material> material)
						: radius(radius), material(material) {
}

bool SphereBase::sphereHit(const Ray& r, double t_min, double t_max,
							HitRecord& rec, const Point3d &center) const {

	Vector3d oc = r.origin - center;
    double a = r.direction.lenghtSquared();
    double half_b = dot(oc, r.direction);
    double c = oc.lenghtSquared() - radius*radius;

    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0){
		return false;
	}
    double sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
		}
    }

    rec.t = root;
    rec.point = r.at(rec.t);
    rec.setFaceNormal(r, (rec.point - center) / radius);
    rec.material = material;

    return true;

}

SphereBase::~SphereBase() {
}
