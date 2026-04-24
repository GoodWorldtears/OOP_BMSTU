#pragma once

#include "render/BaseDrawer.h"
#include <QGraphicsScene>

class QtDrawer : public BaseDrawer
{
public:
    explicit QtDrawer(QGraphicsScene *scene) : _scene(scene) {}
    void clear() override;
    void drawLine(const DrawPoint &start, const DrawPoint &end) override;

private:
    QGraphicsScene *_scene {nullptr};
};
