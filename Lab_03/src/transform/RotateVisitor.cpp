#include "transform/RotateVisitor.h"
#include "scene/BaseBoneModel.h"
#include "scene/Composite.h"
#include "scene/Point.h"
#include <cmath>

namespace
{
constexpr double PI_VALUE = 3.14159265358979323846;

Vector3D rotateAroundX(const Vector3D &v, double angle)
{
    const double r = angle * PI_VALUE / 180.0;
    return {v.x, v.y * std::cos(r) - v.z * std::sin(r), v.y * std::sin(r) + v.z * std::cos(r)};
}

Vector3D rotateAroundY(const Vector3D &v, double angle)
{
    const double r = angle * PI_VALUE / 180.0;
    return {v.x * std::cos(r) + v.z * std::sin(r), v.y, -v.x * std::sin(r) + v.z * std::cos(r)};
}

Vector3D rotateAroundZ(const Vector3D &v, double angle)
{
    const double r = angle * PI_VALUE / 180.0;
    return {v.x * std::cos(r) - v.y * std::sin(r), v.x * std::sin(r) + v.y * std::cos(r), v.z};
}
}

RotateVisitor::RotateVisitor(Vector3D anglesDegrees) : _anglesDegrees(anglesDegrees) {}

void RotateVisitor::visit(BaseBoneModel &model)
{
    for (Point &point : model.structure().points())
    {
        Vector3D value = point.position();
        value = rotateAroundX(value, _anglesDegrees.x);
        value = rotateAroundY(value, _anglesDegrees.y);
        value = rotateAroundZ(value, _anglesDegrees.z);
        point.position() = value;
    }
}

void RotateVisitor::visit(Composite &composite)
{
    for (const auto &object : composite.objects())
    {
        auto transformable = std::dynamic_pointer_cast<TransformableObject>(object);
        if (transformable)
            transformable->accept(*this);
    }
}
