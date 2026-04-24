#pragma once

#include "scene/AbstractObject.h"

class Camera : public AbstractObject
{
public:
    explicit Camera(const Vector3D &position = {0.0, 0.0, -400.0}, QString name = "Camera");

    bool isVisible() const override { return false; }
    void accept(Visitor &visitor) override;

    const Vector3D &position() const { return _position; }
    const Vector3D &rotation() const { return _rotation; }
    void setPosition(const Vector3D &position) { _position = position; }

private:
    Vector3D _position;
    Vector3D _rotation;
};
