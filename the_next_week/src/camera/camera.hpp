#ifndef CAMERA
#define CAMERA

#include "../headers/debug.hpp"
#include "../vector_3d/vector_3d.hpp"
#include "../ray/ray.hpp"
#include "../utils/numbers.hpp"

#define VIEWPORT_HEIGHT 2.0
#define VIEWPORT_WIDTH  (ASPECT_RATIO * VIEWPORT_HEIGHT)
#define FOCAL_LENGTH    1.0

class Camera {
private:
    Point3d origin;
    Vector3d horizontal;
    Vector3d vertical;
    Vector3d lower_left_corner;
    Vector3d w;
    Vector3d u;
    Vector3d v;
    double lens_radius;
    double initial_time, final_time;
public:
    Camera( const Point3d &look_from = Point3d(0, 0, 0),
            const Point3d &look_at = Point3d(0, 0, -1),
            const Vector3d &up = Vector3d(0, 1, 0),
            double fov = 90, double aperture = 0.0,
            double initial_time = 0.0, double final_time = 0.0);

    Ray getRay(double u, double v) const;

    ~Camera();
};

#endif // CAMERA
