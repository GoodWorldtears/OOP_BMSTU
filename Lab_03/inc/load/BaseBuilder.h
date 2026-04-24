#pragma once

#include "load/ModelData.h"
#include "scene/BaseModel.h"
#include <memory>

class BaseBuilder
{
public:
    virtual ~BaseBuilder() = default;
    virtual std::shared_ptr<VisibleObject> build(const ModelData &data) const = 0;
};
