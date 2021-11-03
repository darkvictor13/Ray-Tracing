#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <cmath>
#include "../utils/numbers.hpp"

struct Vector3d {
    union {
        double array[3];
        struct {
            double x, y, z;
        };
        struct {
            double red, green, blue;
        };
    };

    Vector3d();
    Vector3d(double d1, double d2, double d3);

    // operações com o vetor matemático
    Vector3d operator - () const;
    double operator [] (int i) const;
    double& operator [] (int i);

    Vector3d& operator += (const Vector3d &v);
    Vector3d& operator *= (const double t);
    Vector3d& operator /= (const double t);

    static Vector3d random();
    static Vector3d random(double min, double max);

    double lenght() const;
    double lenghtSquared() const;

    bool aproximalyZero() const;

    // funções auxiliares que recebem a classe como parâmetro
    friend std::ostream& operator << (std::ostream &out, const Vector3d &v);
    friend Vector3d operator + (const Vector3d &v1, const Vector3d &v2);
    friend Vector3d operator - (const Vector3d &v1, const Vector3d &v2);
    friend Vector3d operator * (const Vector3d &u, const Vector3d &v);
    friend Vector3d operator * (const double t, const Vector3d &v);
    friend Vector3d operator * (const Vector3d &v, const double t);
    friend Vector3d operator / (Vector3d v, const double t);

    friend double dot(const Vector3d &v1, const Vector3d &v2);
    friend Vector3d cross(const Vector3d &v1, const Vector3d &v2);
    friend Vector3d unitVector(Vector3d v);
    friend Vector3d randomInHemisphere(const Vector3d &normal);
    friend Vector3d reflect(const Vector3d &v1, const Vector3d &v2);
    friend Vector3d refract(const Vector3d &uv, const Vector3d &n, double etai_over_etat);
};

Vector3d randomInUnitSphere();

Vector3d randomInUnitDisk();

using Point3d = Vector3d;
using Color = Vector3d;

#endif // VECTOR
