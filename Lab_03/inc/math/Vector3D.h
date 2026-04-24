#pragma once

#include <cmath>

class Vector3D
{
public:
    double x {0.0};
    double y {0.0};
    double z {0.0};

    Vector3D() = default;
    Vector3D(double xValue, double yValue, double zValue) : x(xValue), y(yValue), z(zValue) {}

    Vector3D operator+(const Vector3D &other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vector3D operator-(const Vector3D &other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vector3D operator*(double factor) const { return {x * factor, y * factor, z * factor}; }
    Vector3D &operator+=(const Vector3D &other)
    {
        x += other.x; y += other.y; z += other.z; return *this;
    }

    double dot(const Vector3D &other) const { return x * other.x + y * other.y + z * other.z; }
    Vector3D cross(const Vector3D &other) const
    {
        return {y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x};
    }

    double length() const { return std::sqrt(dot(*this)); }
    Vector3D normalized() const
    {
        const double len = length();
        if (len == 0.0)
            return {};
        return {x / len, y / len, z / len};
    }
};
