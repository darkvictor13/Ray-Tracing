#ifndef DIELETRIC
#define DIELETRIC

#include "material.hpp"

struct Dieletric : Material {
    double ir;

    Dieletric(double ir = 0.0);

    virtual bool scatter(
            const Ray &r_in,
            const HitRecord &rec,
            Color &attenuation,
            Ray &scattered
        )const override;

    private: static double reflectance(double cos_i, double ref_i);
};


#endif // DIELETRIC
