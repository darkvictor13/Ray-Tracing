#include "vector.hpp"

using utils::randomDouble;

Vector3d::Vector3d() 
    : array{0, 0, 0} {}

Vector3d::Vector3d(double d1, double d2, double d3)
    : array{d1, d2, d3} {}

double Vector3d::x() const {
    return array[0];
}

double Vector3d::y() const {
    return array[1];
}

double Vector3d::z() const {
    return array[2];
}

double Vector3d::red() const {
    return array[0];
}

double Vector3d::green() const {
    return array[1];
}

double Vector3d::blue() const {
    return array[2];
}

Vector3d Vector3d::operator - () const {
    return Vector3d(-array[0], -array[1], -array[2]);
}

double Vector3d::operator [](int i) const {
    return array[i];
}

double& Vector3d::operator [](int i) {
    return array[i];
}

Vector3d& Vector3d::operator += (const Vector3d &v) {
    array[0] += v.array[0];
    array[1] += v.array[1];
    array[2] += v.array[2];
    return *this;
}

Vector3d& Vector3d::operator *= (const double t) {
    array[0] *= t;
    array[1] *= t;
    array[2] *= t;
    return *this;
}

Vector3d& Vector3d::operator /= (const double t) {
    return *this *= 1/t;
}

double Vector3d::lenghtSquared() const {
    return (array[0] * array[0] +
            array[1] * array[1] +
            array[2] * array[2]);
}

double Vector3d::lenght() const {
    return std::sqrt(lenghtSquared());
}

std::ostream& operator << (std::ostream &out, const Vector3d &v) {
    return out << v.array[0] << ' ' << v.array[1] << ' ' << v.array[2];
}

Vector3d operator + (const Vector3d &v1, const Vector3d &v2) {
    return Vector3d(v1.array[0] + v2.array[0],
                    v1.array[1] + v2.array[1],
                    v1.array[2] + v2.array[2]);
}

Vector3d operator - (const Vector3d &v1, const Vector3d &v2) {
    return Vector3d(v1.array[0] - v2.array[0],
                    v1.array[1] - v2.array[1],
                    v1.array[2] - v2.array[2]);
}

Vector3d operator * (const Vector3d &v1, const Vector3d &v2) {
    return Vector3d(v1.array[0] * v2.array[0],
                    v1.array[1] * v2.array[1],
                    v1.array[2] * v2.array[2]);
}

Vector3d operator * (double t, const Vector3d &v) {
    return Vector3d(t * v.array[0], t * v.array[1], t * v.array[2]);
}

Vector3d operator * (const Vector3d &v, double t) {
    return t * v;
}

Vector3d operator / (Vector3d v, double t) {
    return (1/t) * v;
}

double dot(const Vector3d &v1, const Vector3d &v2) {
    return (v1.array[0] * v2.array[0] +
            v1.array[1] * v2.array[1] +
            v1.array[2] * v2.array[2]);
}

Vector3d cross(const Vector3d &v1, const Vector3d &v2) {
    return Vector3d(v1.array[1] * v2.array[2] - v1.array[2] * v2.array[1],
                    v1.array[2] * v2.array[0] - v1.array[0] * v2.array[2],
                    v1.array[0] * v2.array[1] - v1.array[1] * v2.array[0]);
}

Vector3d Vector3d::random() {
    return Vector3d(randomDouble(), randomDouble(), randomDouble());
}

Vector3d Vector3d::random(double min, double max) {
    return Vector3d(randomDouble(min, max),
            randomDouble(min, max), randomDouble(min, max));
}

Vector3d unitVector(Vector3d v) {
    return v / v.lenght();
}

Vector3d randomInUnitSphere() {
    Vector3d p = Vector3d::random(-1,1);
    while (p.lenghtSquared() >= 1) {
        p = Vector3d::random(-1,1);
    }
    return p;
}
