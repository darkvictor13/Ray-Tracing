#ifndef METAL
#define METAL
#include "material.hpp"

struct Metal : Material {
    Color a;
    double fuzz;

    Metal();
    Metal(Color c, double f);

    virtual bool scatter(
            const Ray &r_in,
            const HitRecord &rec,
            Color &attenuation,
            Ray &scattered
        )const override;
};



#endif // METAL
