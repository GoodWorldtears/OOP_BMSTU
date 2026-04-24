#pragma once

#include "scene/ModelStructure.h"

class ListModelStructure : public ModelStructure
{
public:
    ListModelStructure() = default;
    ListModelStructure(std::vector<Point> points,
                       std::vector<Edge> edges);

    std::vector<Point> &points() override { return _points; }
    const std::vector<Point> &points() const override { return _points; }
    std::vector<Edge> &edges() override { return _edges; }
    const std::vector<Edge> &edges() const override { return _edges; }

private:
    std::vector<Point> _points;
    std::vector<Edge> _edges;
};
