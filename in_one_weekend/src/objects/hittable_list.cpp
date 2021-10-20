#include "hittable_list.hpp"

HittableList::HittableList(int min_qnt) {
	objects.reserve(min_qnt);
}

HittableList::HittableList(std::shared_ptr<Hittable> obj) :
	objects {obj} {
}

void HittableList::insert(std::shared_ptr<Hittable> obj) {
    objects.push_back(obj);
}

void HittableList::clear() {
	objects.clear();
}

bool HittableList::hit(const Ray& r, double t_min, double t_max,
						HitRecord& rec) const {

	HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;

}

HittableList::~HittableList() {
    clear();
}
