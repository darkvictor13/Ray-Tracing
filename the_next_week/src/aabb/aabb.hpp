#ifndef AABB
#define AABB

#include "../vector_3d/vector_3d.hpp"
#include "../ray/ray.hpp"

struct Aabb {
	Point3d minimum;
	Point3d maximum;

	Aabb();
	Aabb(const Point3d &begin, const Point3d &end);

	bool inBoundingBox(const Ray &ray, double min, double max) const;

	friend Aabb surroundingBox(const Aabb &box1, const Aabb &box2);

	~Aabb();
};

#endif // AABB
