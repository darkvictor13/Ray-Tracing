#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.hpp"
#include "sphere_static.hpp"
#include "sphere_moving.hpp"
#include "../materials/dieletric.hpp"
#include "../materials/lambertian.hpp"
#include "../materials/metal.hpp"
#include "../materials/material.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable {
private:
	std::vector<std::shared_ptr<Hittable>> objects;

public:
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
