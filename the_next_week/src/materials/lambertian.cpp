#include "lambertian.hpp"

Lambertian::Lambertian() : a() {}

Lambertian::Lambertian(Color c) : a(c) {}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// o raio de entrada r_in não é utilizado nessa função
// porém utilizado no Material metal, por isso desativo esse warning
bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec,
    Color &attenuation, Ray &scattered) const {

    auto scatter_direction = rec.normal + randomInUnitSphere();

    // Catch degenerate scatter direction
    if (scatter_direction.aproximalyZero()) {
        scatter_direction = rec.normal;
    }

    scattered = Ray(rec.point, scatter_direction, r_in.time);
    attenuation = a;
    return true;
}
#pragma GCC diagnostic pop
