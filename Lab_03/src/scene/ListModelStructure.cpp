#include "scene/ListModelStructure.h"

ListModelStructure::ListModelStructure(std::vector<Point> points,
                                       std::vector<Edge> edges)
    : _points(std::move(points)), _edges(std::move(edges))
{
}
