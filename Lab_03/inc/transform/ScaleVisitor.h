#pragma once

#include "transform/TransformVisitor.h"
#include "math/Vector3D.h"

class ScaleVisitor : public TransformVisitor
{
public:
    explicit ScaleVisitor(Vector3D factors);

    void visit(BaseBoneModel &model) override;
    void visit(Composite &composite) override;

private:
    Vector3D _factors;
};
