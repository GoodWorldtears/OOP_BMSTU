#pragma once

#include "transform/TransformVisitor.h"
#include "math/Vector3D.h"

class MoveVisitor : public TransformVisitor
{
public:
    explicit MoveVisitor(Vector3D delta);

    void visit(BaseBoneModel &model) override;
    void visit(Composite &composite) override;

private:
    Vector3D _delta;
};
