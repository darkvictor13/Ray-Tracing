#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <cmath>

struct Vector3d {
    double array[3];

    Vector3d();
    Vector3d(double d1, double d2, double d3);

    double x() const;
    double y() const;
    double z() const;

    double red() const;
    double green() const;
    double blue() const;

    // operações com o vetor matemático
    Vector3d operator - () const;
    double operator [] (int i) const;
    double& operator [] (int i);

    Vector3d& operator += (const Vector3d &v);
    Vector3d& operator *= (const double t);
    Vector3d& operator /= (const double t);

    double lenghtSquared() const;

    double lenght() const;

    // funções auxiliares que recebem a classe como parâmetro
    friend std::ostream& operator << (std::ostream &out, const Vector3d &v);
    friend Vector3d operator + (const Vector3d &v1, const Vector3d &v2);
    friend Vector3d operator - (const Vector3d &v1, const Vector3d &v2);
    friend Vector3d operator * (const Vector3d &u, const Vector3d &v);
    friend Vector3d operator * (double t, const Vector3d &v);
    friend Vector3d operator * (const Vector3d &v, double t);
    friend Vector3d operator / (Vector3d v, double t);

    friend double dot(const Vector3d &v1, const Vector3d &v2);
    friend Vector3d cross(const Vector3d &v1, const Vector3d &v2);
    friend Vector3d unitVector(Vector3d v);
};


using Point3d = Vector3d;
using Color = Vector3d;

#endif // VECTOR
