#include <iomanip>
#include <cmath>
#include <math.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <thread>

#include "vector_3d/vector_3d.hpp"
#include "ray/ray.hpp"

#include "objects/hittable.hpp"
#include "objects/sphere.hpp"
#include "objects/hittable_list.hpp"

#include "materials/material.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"

#include "utils/numbers.hpp"

#include "camera/camera.hpp"
#include "camera/ppm_writer.hpp"

#include "headers/debug.hpp"
#include "utils/scope_timer.hpp"

Color rayColor (const Ray& r, const Hittable& world, int8_t depht);

inline double hitSphere(const Point3d& center, double radius, const Ray& r);

std::string getFileName();

void generateImagePart(const uint16_t id, const int height_initial, const int height_final,
        const HittableList &world, Color m[][IMAGE_WIDTH], const Camera &cam);

int main (int argc, char *argv[]) {
#if DEBUG_VAR
    ScopeTimer timer(__func__);
#endif
    Color image[IMAGE_HEIGHT][IMAGE_WIDTH];
    Camera cam;
    HittableList world(4);
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    std::string file_name = (argc == 2? argv[1] : getFileName());
    {
        const auto it = file_name.find_last_of('.');
        if (it == file_name.npos) {
            file_name += ".ppm";
        }
        file_name.insert(0, IMAGE_PATH);
    }

    world.insert(std::make_shared<Sphere>(Point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.insert(std::make_shared<Sphere>(Point3d( 0.0,    0.0, -1.0),   0.5, material_center));
    world.insert(std::make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    world.insert(std::make_shared<Sphere>(Point3d( 1.0,    0.0, -1.0),   0.5, material_right));

    debug("Nome do arquivo " << file_name << '\n');
    PpmWriter writer(file_name);
    writer.writeHeader();

    debug("Construindo as Threads\n");
    std::vector<std::thread> threds;
    {
        const int height_sep = IMAGE_HEIGHT / CPU_CORES;
        const int lim = CPU_CORES-1;
        int height_sum = 0;

        for (uint16_t i = 0; i < lim; i++) {
            threds.push_back(std::thread(
                generateImagePart, i,
                height_sum, height_sum + height_sep,
                world, image, cam
            ));
            height_sum += height_sep;
        }
        threds.push_back(std::thread(
                    generateImagePart,
                    static_cast<uint16_t>(CPU_CORES-1),
                    height_sum, IMAGE_HEIGHT,
                    world, image, cam)
                );
    }

    debug("Aguardando as threads finalizarem\n");
    for (auto &it : threds) {
        it.join();
    }

    debug("Escrevendo a imagem em " << file_name << '\n');
    writer.writeImage(image);

    return 0;
}

Color rayColor(const Ray& r, const Hittable& world, int8_t depht) {
    HitRecord rec;
    if (depht < 1) {
        return Color(0, 0, 0);
    }
    if (world.hit(r, 0.001, utils::INF, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * rayColor(scattered, world, depht-1);
        }
        return Color(0,0,0);
    }
    auto unit_direction = unitVector(r.direction);
    double t = 0.5*(unit_direction.green + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

double hitSphere(const Point3d& center, double radius, const Ray& r) {
    Vector3d oc = r.origin - center;
    auto a = r.direction.lenghtSquared();
    auto half_b = dot(oc, r.direction);
    auto c = oc.lenghtSquared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    return (discriminant < 0? -1.0 : (-half_b - std::sqrt(discriminant)) / a);
}

std::string getFileName() {
    using namespace std;
    char input;
    string file_name;
    cout << "Deseja inserir o nome do arquivo? [s/N] ";
    cin.get(input);
    if (tolower(input) == 's') {
        cout << "Entre com o nome do arquivo: ";
        cin >> file_name;
    }else{
        file_name = DEFAULT_FILE_NAME;
    }
    return file_name;
}

void generateImagePart(const uint16_t id, const int height_initial, const int height_final,
        const HittableList &world, Color m[][IMAGE_WIDTH], const Camera &cam) {
#if DEBUG_VAR
    ScopeTimer timer("Thread " + std::to_string(id) + ", " + __func__);
#endif

    debug("Thread " << id << " vai escrever das linhas: ["
        << height_initial << ", " << height_final << ")\n");

    int i, j, s;
    for (i = height_initial; i < height_final; i++) {
        for (j = 0; j < IMAGE_WIDTH; j++) {
            Color pixel_color(0, 0, 0);
            for (s = 0; s < SAMPLES_PER_PIXEL; s++) {
                auto u = (j + utils::randomDouble()) / (IMAGE_WIDTH-1);
                auto v = ((IMAGE_HEIGHT - (i + 1)) + utils::randomDouble()) / (IMAGE_HEIGHT-1);
                Ray r = cam.getRay(u, v);
                pixel_color += rayColor(r, world, MAX_DEPTH);
            }
            m[i][j] = pixel_color;
        }
    }
}
