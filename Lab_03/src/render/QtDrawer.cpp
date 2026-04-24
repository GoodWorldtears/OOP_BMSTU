#include "render/QtDrawer.h"
#include <QLineF>
#include <QPen>

void QtDrawer::clear()
{
    if (_scene)
        _scene->clear();
}

void QtDrawer::drawLine(const DrawPoint &start, const DrawPoint &end)
{
    if (_scene)
        _scene->addLine(QLineF(start.x, start.y, end.x, end.y), QPen(Qt::black));
}
