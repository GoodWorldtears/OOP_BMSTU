#pragma once

#include "render/BaseDrawer.h"
#include <memory>

class BaseRenderSurface;

class BaseRenderFactory
{
public:
    virtual ~BaseRenderFactory() = default;
    virtual std::unique_ptr<BaseDrawer> createDrawer(BaseRenderSurface &surface) const = 0;
};
