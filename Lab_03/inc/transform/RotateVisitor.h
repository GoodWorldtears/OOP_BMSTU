#pragma once

#include "transform/TransformVisitor.h"
#include "math/Vector3D.h"

class RotateVisitor : public TransformVisitor
{
public:
    explicit RotateVisitor(Vector3D anglesDegrees);

    void visit(BaseBoneModel &model) override;
    void visit(Composite &composite) override;

private:
    Vector3D _anglesDegrees;
};
