#ifndef HITTABLE
#define HITTABLE

#include "../ray/ray.hpp"
#include "../aabb/aabb.hpp"
#include <memory>

struct Material;

struct HitRecord {
    Point3d point;
    Vector3d normal;
    std::shared_ptr<Material> material;
    bool front_face;
    double t;

    void setFaceNormal(const Ray& r,
            const Vector3d& outward_normal);
};

/**
 * @brief Classe abstrata que serve de interface para todos os objetos
 * que são atingidos por raios de luz
 * 
 * utilizou-se uma struct devido a tudo ser publico
 */
struct Hittable {
    virtual bool hit(const Ray& r, double t_min, double t_max,
            HitRecord& rec) const = 0;

    virtual bool boundingBox(double initial_time,
            double final_time, Aabb &out_box) const = 0;
};

#endif // HITTABLE
