#ifndef LAMBERTIAN
#define LAMBERTIAN

#include "material.hpp"

struct Lambertian : Material {
    Color a;

    Lambertian();
    Lambertian(Color c);

    virtual bool scatter(
            const Ray &r_in,
            const HitRecord &rec,
            Color &attenuation,
            Ray &scattered
        )const override;
};


#endif // LAMBERTIAN
