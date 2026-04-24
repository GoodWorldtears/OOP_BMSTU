#pragma once

#include "math/Vector3D.h"
#include "scene/TransformableObject.h"

class TransformService
{
public:
    void move(TransformableObject &object, const Vector3D &delta) const;
    void rotate(TransformableObject &object, const Vector3D &anglesDegrees) const;
    void scale(TransformableObject &object, const Vector3D &factors) const;
};
