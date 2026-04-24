#pragma once

#include "math/Vector3D.h"

class Point
{
public:
    Point() = default;
    Point(double x, double y, double z) : _position(x, y, z) {}
    explicit Point(const Vector3D &position) : _position(position) {}

    Vector3D &position() { return _position; }
    const Vector3D &position() const { return _position; }

private:
    Vector3D _position;
};
