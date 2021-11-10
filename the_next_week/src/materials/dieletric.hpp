#ifndef DIELETRIC
#define DIELETRIC

#include "material.hpp"

struct Dieletric : public Material {
private:
    double ir;
    static double reflectance(double cos_i, double ref_i);

public:
    Dieletric(double ir = 0.0);

    virtual bool scatter(
        const Ray &r_in,
        const HitRecord &rec,
        Color &attenuation,
        Ray &scattered) const override;
};


#endif // DIELETRIC
