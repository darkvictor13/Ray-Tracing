#include "bvh_node.hpp"

BvhNode::BvhNode() {
}

BvhNode::BvhNode(const HittableList &list, double time_0, double time_1)
	: BvhNode(list.getList(), 0, list.getList().size(), time_0, time_1) {
}

BvhNode::BvhNode(const std::vector<std::shared_ptr<Hittable>> &objs,
		size_t i_begin, size_t i_end, double time_0, double time_1) {
	
	std::vector<std::shared_ptr<Hittable>> actual_objs = {
		objs.begin() + i_begin,
		objs.begin() + i_end
	};
	const int axis = rand() % 3;
	auto comp = [axis] (const std::shared_ptr<Hittable> &first,
						const std::shared_ptr<Hittable> &last) {

		return boxCmp(first, last, axis);
	};

	std::sort(actual_objs.begin(), actual_objs.end(), comp);
}

bool BvhNode::hit(const Ray& r,
        double t_min, double t_max, HitRecord& rec) const {
	
	if (!box.inBoundingBox(r, t_min, t_max)) {
		return false;
	}

	const bool hit_left = left->hit(r, t_min, t_max, rec);
	return hit_left || right->hit(r, t_min, (hit_left? rec.t : t_max), rec);
}

bool BvhNode::boundingBox(double initial_time,
			double final_time, Aabb &out_box) const {
	
	out_box = box;
	return true;
}

BvhNode::~BvhNode() {
    
}

bool boxCmp(const std::shared_ptr<Hittable> &first,
			const std::shared_ptr<Hittable> &last,
			const int axis) {

	Aabb first_box;
	Aabb last_box;
	if (!first->boundingBox(0, 0, first_box) ||
		! last->boundingBox(0, 0, last_box)) {
		
		debug("Não existe bounding Box no construtor\n");
	}

	return first_box.minimum.array[axis] < last_box.minimum.array[axis];
}