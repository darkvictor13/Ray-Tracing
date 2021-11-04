#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.hpp"
#include "sphere.hpp"
#include "../materials/dieletric.hpp"
#include "../materials/lambertian.hpp"
#include "../materials/metal.hpp"
#include "../materials/material.hpp"

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

    void generateRandomScene();

	~HittableList();
};


#endif // HITTABLE_LIST
