#pragma once

#include "render/BaseRenderSurface.h"

class QGraphicsScene;

class QtRenderSurface : public BaseRenderSurface
{
public:
    explicit QtRenderSurface(QGraphicsScene *scene) : _scene(scene) {}
    QGraphicsScene *scene() const { return _scene; }

private:
    QGraphicsScene *_scene {nullptr};
};
