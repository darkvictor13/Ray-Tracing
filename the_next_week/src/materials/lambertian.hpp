#ifndef LAMBERTIAN
#define LAMBERTIAN

#include "material.hpp"

class Lambertian : public Material {
private:
    Color a;

public:
    Lambertian();
    Lambertian(Color c);

    virtual bool scatter(
        const Ray &r_in,
        const HitRecord &rec,
        Color &attenuation,
        Ray &scattered) const override;
};


#endif // LAMBERTIAN
