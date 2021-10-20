#include <iomanip>
#include <iostream>
#include <cctype>
#include <fstream>

#include "vector/vector.hpp"

#include "ray/color.hpp"
#include "ray/ray.hpp"

#include "objects/hittable.hpp"
#include "objects/sphere.hpp"
#include "objects/hittable_list.hpp"

#include "utils/numbers.hpp"

#include "camera/setup.hpp"
#include "camera/camera.hpp"
#include "camera/ppm_writer.hpp"

Color rayColor (const Ray& r, const Hittable& world);

inline double hitSphere(const Point3d& center, double radius, const Ray& r);

std::string getFileName();

int main (int argc, char *argv[]) {

    std::string file_name = (argc == 2? argv[1] : getFileName());
    file_name.insert(0, IMAGE_PATH);

    Camera cam;
    HittableList world(3);
    world.insert(std::make_shared<Sphere>(Point3d(0,0,-1), 0.5));
    world.insert(std::make_shared<Sphere>(Point3d(0,-100.5,-1), 100));
    world.insert(std::make_shared<Sphere>(Point3d(-50,20,-50), 10));

    std::cout << "Nome do arquivo " << file_name << '\n';
    PpmWriter writer(file_name);
    writer.writeHeader();

    int i, j, s;
    for (j = IMAGE_HEIGHT - 1; j >= 0; j--) {
        std::cout << "Faltam " << std::setfill('0') << std::setw(3) << j << " linhas para gerar\n";
        for (i = 0; i < IMAGE_WIDTH; i++) {
            Color pixel_color(0, 0, 0);
            for (s = 0; s < SAMPLES_PER_PIXEL; s++) {
                auto u = (i + utils::randomDouble()) / (IMAGE_WIDTH-1);
                auto v = (j + utils::randomDouble()) / (IMAGE_HEIGHT-1);
                Ray r = cam.getRay(u, v);
                pixel_color += rayColor(r, world);
            }
            writer.writeColor(pixel_color);
        }
    }

    return 0;
}

Color rayColor(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, 0, utils::INF, rec)) {
        return 0.5 * (rec.normal + Color(1,1,1));
    }
    auto unit_direction = unitVector(r.direction);
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

std::string getFileName() {
    using namespace std;
    char input;
    string file_name;
    cout << "Deseja inserir o nome do arquivo? [s/N] ";
    cin.get(input);
    if (tolower(input) == 's') {
        cout << "Entre com o nome do arquivo: ";
        cin >> file_name;
        auto it = file_name.find_last_of('.');
        if (it == file_name.npos) {
            file_name += ".ppm";
        }
    }else{
        file_name = DEFAULT_FILE_NAME;
    }
    return file_name;
}
