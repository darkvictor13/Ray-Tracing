#include "dieletric.hpp"

Dieletric::Dieletric(double ir) : ir(ir) {}

bool Dieletric::scatter(const Ray &r_in, const HitRecord &rec,
        Color &attenuation, Ray &scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    Vector3d unit_direction = unitVector(r_in.direction);
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vector3d direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > utils::randomDouble())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.point, direction, r_in.time);
    return true;
}

double Dieletric::reflectance(double cos_i, double ref_i) {
    auto r0 = (1-ref_i) / (1+ref_i);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cos_i),5);
}

