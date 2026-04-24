#include "scene/Camera.h"
#include "render/Visitor.h"

Camera::Camera(const Vector3D &position, QString name)
    : AbstractObject(std::move(name)), _position(position)
{
}

void Camera::accept(Visitor &visitor)
{
    visitor.visit(*this);
}
