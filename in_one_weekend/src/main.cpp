#include <iomanip>
#include <iostream>
#include <cctype>
#include <fstream>
#include <limits>

#include "vector/vector.hpp"
#include "ray/color.hpp"
#include "ray/ray.hpp"
#include "objects/hittable.hpp"
#include "objects/sphere.hpp"
#include "objects/hittable_list.hpp"

#define IMAGE_PATH        "../images/"
#define DEFAULT_FILE_NAME "bola.ppm"

// Imagem
#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH  400
#define IMAGE_HEIGHT static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO)

// Câmera
#define VIEWPORT_HEIGHT 2.0
#define VIEWPORT_WIDTH  (ASPECT_RATIO * VIEWPORT_HEIGHT)
#define FOCAL_LENGTH    1.0

Color rayColor (const Ray& r, const Hittable& world);
inline double hitSphere(const Point3d& center, double radius, const Ray& r);

int main (int argc, char *argv[]) {

    std::string file_name;
    if (argc == 2) {
        file_name = argv[1];
    } else {
        char input;
        std::cout << "Deseja inserir o nome do arquivo? [s/N] ";
        std::cin.get(input);
        if (std::tolower(input) == 's') {
            std::cout << "Entre com o nome do arquivo: ";
            std::cin >> file_name;
        }else{
            file_name = DEFAULT_FILE_NAME;
        }
    }

    Point3d origin(0, 0, 0);
    Vector3d horizontal(VIEWPORT_WIDTH, 0, 0);
    Vector3d vertical(0, VIEWPORT_HEIGHT, 0);
    Vector3d lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3d(0, 0, FOCAL_LENGTH);

	HittableList world;
    world.insert(std::make_shared<Sphere>(Point3d(0,0,-1), 0.5));
    world.insert(std::make_shared<Sphere>(Point3d(0,-100.5,-1), 100));

    std::ofstream file;
    file.open(IMAGE_PATH + file_name);
    file << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    int i, j;
    
    for (j = IMAGE_HEIGHT - 1; j >= 0; j--) {
        std::cout << "Faltam " << std::setfill('0') << std::setw(3) << j << " linhas para gerar\n";
        for (i = 0; i < IMAGE_WIDTH; i++) {
            auto u = double(i) / (IMAGE_WIDTH-1);
            auto v = double(j) / (IMAGE_HEIGHT-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            writeColor(file, rayColor(r, world));
        }
    }

    file.close();
    return 0;
}

Color rayColor(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec)) {
        return 0.5 * (rec.normal + Color(1,1,1));
    }auto unit_direction = unitVector(r.direction);
    double t = 0.5*(unit_direction.green() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

double hitSphere(const Point3d& center, double radius, const Ray& r) {
    Vector3d oc = r.origin - center;
    auto a = r.direction.lenghtSquared();
    auto half_b = dot(oc, r.direction);
    auto c = oc.lenghtSquared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    return (discriminant < 0? -1.0 : (-half_b - sqrt(discriminant) ) / a);
}
