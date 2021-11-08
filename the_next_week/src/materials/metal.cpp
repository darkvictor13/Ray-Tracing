#include "metal.hpp"

Metal::Metal() : a() {}

Metal::Metal(Color c, double f) : a(c), fuzz(f > 1.0? 1.0 : f) {}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec,
    Color &attenuation, Ray &scattered) const {

    Vector3d reflected = reflect(unitVector(r_in.direction), rec.normal);
    scattered = Ray(rec.point, reflected + (fuzz * randomInUnitSphere()));
    attenuation = a;
    return (dot(scattered.direction, rec.normal) > 0);
}
