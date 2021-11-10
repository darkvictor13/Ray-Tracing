#include "aabb.hpp"

Aabb::Aabb() : minimum(), maximum() {
}

Aabb::Aabb(const Point3d &begin, const Point3d &end) :
			minimum(begin), maximum(end) {
}

bool Aabb::inBoundingBox(const Ray &ray, double min, double max) const {
    for (uint8_t i = 0; i < 3; i++) {
		double inverse_direction = 1.0 / ray.direction[i];
		double initial_p = (minimum[i] - ray.origin[i]) * inverse_direction;
		double final_p   = (maximum[i] - ray.origin[i]) * inverse_direction;

		if (inverse_direction < 0.0) {
			std::swap(initial_p, final_p);
		}

		min = std::max(min, initial_p);
		max = std::min(max, final_p);

		if (max <= min) {
			return false;
		}
	}
	return true;
}

Aabb surroundingBox(const Aabb &box1, const Aabb &box2) {
    const Point3d small(fmin(box1.minimum.x, box2.minimum.x),
						fmin(box1.minimum.y, box2.minimum.y),
						fmin(box1.minimum.z, box2.minimum.z));

    const Point3d big  (fmax(box1.maximum.x, box2.maximum.x),
						fmax(box1.maximum.y, box2.maximum.y),
						fmax(box1.maximum.z, box2.maximum.z));

    return Aabb(small, big);
}

Aabb::~Aabb() {
}
