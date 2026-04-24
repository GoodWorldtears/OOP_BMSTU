#include "transform/ScaleVisitor.h"
#include "scene/BaseBoneModel.h"
#include "scene/Composite.h"
#include "scene/Point.h"

ScaleVisitor::ScaleVisitor(Vector3D factors) : _factors(factors) {}

void ScaleVisitor::visit(BaseBoneModel &model)
{
    for (Point &point : model.structure().points())
    {
        Vector3D &value = point.position();
        value.x *= _factors.x;
        value.y *= _factors.y;
        value.z *= _factors.z;
    }
}

void ScaleVisitor::visit(Composite &composite)
{
    for (const auto &object : composite.objects())
    {
        auto transformable = std::dynamic_pointer_cast<TransformableObject>(object);
        if (transformable)
            transformable->accept(*this);
    }
}
