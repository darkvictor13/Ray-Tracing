#include "hittable_list.hpp"

using utils::randomDouble;

HittableList::HittableList(int min_qnt) {
	objects.reserve(min_qnt);
}

HittableList::HittableList(std::shared_ptr<Hittable> obj)
    : objects {obj} {}

void HittableList::insert(std::shared_ptr<Hittable> obj) {
    objects.push_back(obj);
}

void HittableList::clear() {
	objects.clear();
}

bool HittableList::hit(const Ray& r,
        double t_min, double t_max, HitRecord& rec) const {

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

bool HittableList::boundingBox(double initial_time,
			double final_time, Aabb &out_box) const {
    
    if (objects.empty()) {
        return false;
    }

    Aabb temp;
    bool is_fist_box = true;

    for (const auto &it : objects) {
        if (!it->boundingBox(initial_time, final_time, out_box)) {
            return false;
        }
        if (is_fist_box) {
            out_box = temp;
            is_fist_box = false;
        }else {
            out_box = surroundingBox(temp, out_box);
        }
    }

    return true;
}

void HittableList::generateRandomScene() {
    if (objects.size()) {
        objects.clear();
    }
    objects.reserve(488);
    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    objects.push_back(std::make_shared<SphereStatic>(Point3d(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomDouble();
            Point3d center(a + 0.9*randomDouble(), 0.2, b + 0.9*randomDouble());

            if ((center - Point3d(4, 0.2, 0)).lenght() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center1 = center + Vector3d(0, utils::randomDouble(0,0.5), 0);
                    objects.push_back(std::make_shared<SphereMoving>(
                        center, center1, 0.0, 1, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    objects.push_back(std::make_shared<SphereStatic>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dieletric>(1.5);
                    objects.push_back(std::make_shared<SphereStatic>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dieletric>(1.5);
    objects.push_back(std::make_shared<SphereStatic>(Point3d(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    objects.push_back(std::make_shared<SphereStatic>(Point3d(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    objects.push_back(std::make_shared<SphereStatic>(Point3d(4, 1, 0), 1.0, material3));
}


HittableList::~HittableList() {
    clear();
}
