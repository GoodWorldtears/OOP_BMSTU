#pragma once

#include "render/BaseRenderFactory.h"

class QtRenderFactory : public BaseRenderFactory
{
public:
    std::unique_ptr<BaseDrawer> createDrawer(BaseRenderSurface &surface) const override;
};
