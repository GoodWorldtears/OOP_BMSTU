#include "transform/MoveVisitor.h"
#include "scene/BaseBoneModel.h"
#include "scene/Composite.h"
#include "scene/Point.h"

MoveVisitor::MoveVisitor(Vector3D delta) : _delta(delta) {}

void MoveVisitor::visit(BaseBoneModel &model)
{
    for (Point &point : model.structure().points())
        point.position() += _delta;
}

void MoveVisitor::visit(Composite &composite)
{
    for (const auto &object : composite.objects())
    {
        auto transformable = std::dynamic_pointer_cast<TransformableObject>(object);
        if (transformable)
            transformable->accept(*this);
    }
}
