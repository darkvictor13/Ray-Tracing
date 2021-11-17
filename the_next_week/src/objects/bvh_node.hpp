#ifndef BVH_NODE
#define BVH_NODE

#include "hittable_list.hpp"
#include "../headers/debug.hpp"

class BvhNode : public Hittable {
private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	Aabb box;
public:
	BvhNode();
	BvhNode(const HittableList &list, double time_0, double time_1);
	BvhNode(const std::vector<std::shared_ptr<Hittable>> &objs,
		size_t i_begin, size_t i_end, double time_0, double time_1);

	virtual bool hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const override;

    virtual bool boundingBox(double initial_time,
            double final_time, Aabb &out_box) const override;

	~BvhNode();
};

bool boxCmp(const std::shared_ptr<Hittable> &first,
			const std::shared_ptr<Hittable> &last,
			const int axis);

#endif // BVH_NODE
