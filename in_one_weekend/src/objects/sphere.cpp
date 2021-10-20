#include "sphere.hpp"

Sphere::Sphere() : center(), radius() {}

Sphere::Sphere(Point3d center, double radius) :
	center(center), radius(radius) {}

bool Sphere::hit(const Ray& r, double t_min, double t_max,
				HitRecord& rec) const {
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

    return true;
}
