#include <iomanip>
#include <cmath>
#include <math.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <thread>
#include <utility>

#include "headers/user_config.hpp"
#include "vector_3d/vector_3d.hpp"
#include "ray/ray.hpp"

#include "objects/hittable.hpp"
#include "objects/sphere_static.hpp"
#include "objects/hittable_list.hpp"

#include "materials/material.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"
#include "materials/dieletric.hpp"

#include "utils/numbers.hpp"

#include "camera/camera.hpp"
#include "ppm_writer/ppm_writer.hpp"

#include "headers/debug.hpp"
#include "utils/scope_timer.hpp"

#define MAX_DEPTH 50

Color rayColor (const Ray& r, const Hittable& world, int8_t depht);

inline double hitSphere(const Point3d& center, double radius, const Ray& r);

std::string getFileName();

std::pair<Point3d, Point3d> getCameraPosition();

bool getUserResponse(bool default_return);

Point3d getUserInputPoint();

void generateImagePart(const uint16_t id, const int height_initial, const int height_final,
        const HittableList &world, ColorRep m[][IMAGE_WIDTH], const Camera &cam);

int main (int argc, char *argv[]) {
#if DEBUG_VAR
    ScopeTimer timer(__func__);
#endif
    ColorRep image[IMAGE_HEIGHT][IMAGE_WIDTH];
    HittableList world;

    std::string file_name = (argc == 2? argv[1] : getFileName());
    {
        const auto it = file_name.find_last_of('.');
        if (it == file_name.npos) {
            file_name += ".ppm";
        }
        file_name.insert(0, IMAGE_PATH);
    }

    world.generateRandomScene();

    debug("Nome do arquivo " << file_name << '\n');
    PpmWriter writer(file_name);
    writer.writeHeader();

    auto cam_config = getCameraPosition();
    Camera cam(cam_config.first, cam_config.second, Vector3d(0, 1, 0), 20, 0.1, 0.0, 1.0);

    debug("Construindo as Threads\n");
    std::vector<std::thread> threds;
    {
        auto concurrent_threads = std::thread::hardware_concurrency();

        if (concurrent_threads != CPU_CORES) {
            std::cout << "No arquivo de config está definido que vc tem " <<
                CPU_CORES << " threads,\nmas o c++ diz que vc tem " << concurrent_threads <<
                " quantas threads seu computador tem?\n(Quantidade de threads da CPU) -> ";

            unsigned int input_number_of_concurrent_threads;
            std::cin >> input_number_of_concurrent_threads;
            concurrent_threads = input_number_of_concurrent_threads;
        }

        const int height_sep = IMAGE_HEIGHT / concurrent_threads;
        const int lim = concurrent_threads-1;
        int height_sum = 0;

        threds.reserve(concurrent_threads);

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
                    static_cast<uint16_t>(concurrent_threads-1),
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
    if (world.hit(r, 0.001, INF, rec)) {
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
    string file_name;
    cout << "Deseja inserir o nome do arquivo? [s/N] ";
    if (getUserResponse(false)) {
        cout << "Entre com o nome do arquivo: ";
        cin >> file_name;
    }else{
        file_name = DEFAULT_FILE_NAME;
    }
    return file_name;
}

void generateImagePart(const uint16_t id, const int height_initial, const int height_final,
        const HittableList &world, ColorRep m[][IMAGE_WIDTH], const Camera &cam) {
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
        debug("Finalizado a linha " << i << '\n');
    }
}

std::pair<Point3d, Point3d> getCameraPosition() {
    Point3d look_from;
    Point3d look_at;
    std::cout << "Deseja entrar com informações da câmera? [S/n] ";
    if (getUserResponse(true)) {
        std::cout << "Em que posição está localizada a câmera?\n";
        look_from = getUserInputPoint();
        std::cout << "Para que ponto a câmera está apontando?\n";
        look_at = getUserInputPoint();
    }else {
        look_from = Point3d(13, 2, 3);
        look_at = Point3d(0, 0, 0);
    }
    std::pair<Point3d, Point3d> ret(look_from, look_at);
    return ret;
}

bool getUserResponse(bool default_return) {
    char input;
    std::cin.get(input);
    input = std::tolower(input);
    if (input == 's') {
        return true;
    }
    if (input == 'n') {
        return false;
    }
    return default_return;
}

Point3d getUserInputPoint() {
    using namespace std;
    double x, y, z;

    cout << "Coordenada x: ";
    cin >> x;
    cout << "Coordenada y: ";
    cin >> y;
    cout << "Coordenada z: ";
    cin >> z;

    return {x, y, z};
}
