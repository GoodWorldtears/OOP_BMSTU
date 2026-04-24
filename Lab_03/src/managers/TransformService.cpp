#include "managers/TransformService.h"
#include "transform/MoveVisitor.h"
#include "transform/RotateVisitor.h"
#include "transform/ScaleVisitor.h"

void TransformService::move(TransformableObject &object, const Vector3D &delta) const
{
    MoveVisitor visitor(delta);
    object.accept(visitor);
}

void TransformService::rotate(TransformableObject &object, const Vector3D &anglesDegrees) const
{
    RotateVisitor visitor(anglesDegrees);
    object.accept(visitor);
}

void TransformService::scale(TransformableObject &object, const Vector3D &factors) const
{
    ScaleVisitor visitor(factors);
    object.accept(visitor);
}
