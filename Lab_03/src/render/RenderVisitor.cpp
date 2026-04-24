#include "render/RenderVisitor.h"
#include "scene/BaseBoneModel.h"
#include "scene/Composite.h"
#include "scene/Camera.h"
#include "scene/Scene.h"

RenderVisitor::RenderVisitor(std::unique_ptr<BaseDrawer> drawer, const Scene &scene)
    : _drawer(std::move(drawer)), _scene(scene)
{
    _drawer->clear();
}

bool RenderVisitor::projectPoint(const Vector3D &worldPoint, DrawPoint &screenPoint) const
{
    const auto camera = _scene.activeCamera();
    if (!camera)
        return false;

    const Vector3D relative = worldPoint - camera->position();
    const double depth = relative.z + 700.0;
    if (depth <= 1.0)
        return false;

    const double focal = 500.0;
    screenPoint.x = relative.x * focal / depth;
    screenPoint.y = -relative.y * focal / depth;
    return true;
}

void RenderVisitor::visit(BaseBoneModel &model)
{
    const auto &points = model.structure().points();
    const auto &edges = model.structure().edges();

    for (const Edge &edge : edges)
    {
        DrawPoint p1;
        DrawPoint p2;
        if (projectPoint(points.at(edge.first()).position(), p1) && projectPoint(points.at(edge.second()).position(), p2))
            _drawer->drawLine(p1, p2);
    }
}

void RenderVisitor::visit(Composite &composite)
{
    for (const auto &object : composite.objects())
        object->accept(*this);
}

void RenderVisitor::visit(Camera &)
{
}
