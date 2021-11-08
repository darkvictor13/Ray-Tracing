#ifndef MATERIAL
#define MATERIAL

#include "../vector_3d/vector_3d.hpp"
#include "../ray/ray.hpp"
#include "../objects/hittable.hpp"

struct Material {
    virtual bool scatter
            (
                const Ray &r_in,
                const HitRecord &rec,
                Color &attenuation,
                Ray &scattered
            ) const = 0;
};


#endif // MATERIAL
