#ifndef METAL
#define METAL
#include "material.hpp"

class Metal : public Material {
private:
    Color a;
    double fuzz;

public:
    Metal();
    Metal(Color c, double f);

    virtual bool scatter(
        const Ray &r_in,
        const HitRecord &rec,
        Color &attenuation,
        Ray &scattered) const override;
};



#endif // METAL
