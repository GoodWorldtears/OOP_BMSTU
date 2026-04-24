#pragma once

#include "scene/Point.h"
#include "scene/Edge.h"
#include <vector>
#include <QString>

struct ModelData
{
    QString name {"Model"};
    std::vector<Point> points;
    std::vector<Edge> edges;
};
