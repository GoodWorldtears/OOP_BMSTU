#pragma once

#include "render/Visitor.h"
#include "render/BaseDrawer.h"
#include <memory>

class Scene;
class Vector3D;

class RenderVisitor : public Visitor
{
public:
    RenderVisitor(std::unique_ptr<BaseDrawer> drawer, const Scene &scene);

    void visit(BaseBoneModel &model) override;
    void visit(Composite &composite) override;
    void visit(Camera &camera) override;

private:
    std::unique_ptr<BaseDrawer> _drawer;
    const Scene &_scene;

    bool projectPoint(const Vector3D &worldPoint, DrawPoint &screenPoint) const;
};
