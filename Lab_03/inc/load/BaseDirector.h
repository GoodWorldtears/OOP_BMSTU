#pragma once

#include "load/ModelData.h"
#include "scene/BaseModel.h"
#include <memory>

class BaseDirector
{
public:
    virtual ~BaseDirector() = default;
    virtual std::shared_ptr<VisibleObject> construct(const ModelData &data) const = 0;
};
