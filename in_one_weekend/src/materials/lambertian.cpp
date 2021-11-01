#include "lambertian.hpp"

Lambertian::Lambertian() : a() {}

Lambertian::Lambertian(Color c) : a(c) {}

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec,
    Color &attenuation, Ray &scattered) const {

    auto scatter_direction = rec.normal + randomInUnitSphere();

    // Catch degenerate scatter direction
    if (scatter_direction.aproximalyZero()) {
        scatter_direction = rec.normal;
    }

    scattered = Ray(rec.point, scatter_direction);
    attenuation = a;
    return true;
}

