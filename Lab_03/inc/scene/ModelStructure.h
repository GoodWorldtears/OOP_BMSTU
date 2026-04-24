#pragma once

#include "scene/Point.h"
#include "scene/Edge.h"
#include <vector>
#include <memory>

class ModelStructure
{
public:
    virtual ~ModelStructure() = default;
    virtual std::vector<Point> &points() = 0;
    virtual const std::vector<Point> &points() const = 0;
    virtual std::vector<Edge> &edges() = 0;
    virtual const std::vector<Edge> &edges() const = 0;
};

using ModelStructurePtr = std::shared_ptr<ModelStructure>;
