#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.hpp"

#include <memory>
#include <vector>

struct HittableList : public Hittable {
	std::vector<std::shared_ptr<Hittable>> objects;

	HittableList(int min_qnt = 1);
	HittableList(std::shared_ptr<Hittable> obj);

	void insert(std::shared_ptr<Hittable> obj);
	void clear();

	virtual bool hit(const Ray& r, double t_min, double t_max,
					HitRecord& rec) const override;

	~HittableList();
};


#endif // HITTABLE_LIST
