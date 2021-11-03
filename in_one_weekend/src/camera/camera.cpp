#include "camera.hpp"

Camera::Camera( const Point3d &look_from,
        const Point3d &look_at,
        const Vector3d &up,
        double fov, double aperture) {

    double h = tan(utils::degreesToRadians(fov) / 2);
    double viewport_height = 2.0 * h;
    double viewport_width = ASPECT_RATIO * viewport_height;
    double focus_dist = (look_from - look_at).lenght();

    w = unitVector(look_from - look_at);
    u = unitVector(cross(up, w));
    v = cross(w, u);

    origin = look_from;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * w;

    lens_radius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const {
    Vector3d rd = lens_radius * randomInUnitDisk();
    Vector3d offset = u * rd.x + v * rd.y;
    return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}

Camera::~Camera() {}
