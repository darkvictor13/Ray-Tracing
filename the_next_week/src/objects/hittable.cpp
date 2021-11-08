#include "hittable.hpp"

void HitRecord::setFaceNormal(const Ray& r,
				const Vector3d& outward_normal) {

    front_face = dot(r.direction, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}