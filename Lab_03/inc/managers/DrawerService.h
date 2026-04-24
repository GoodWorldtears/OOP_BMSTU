#pragma once

#include "render/BaseRenderFactory.h"
#include "render/QtRenderFactory.h"
#include <memory>

class Scene;
class BaseRenderSurface;

class RenderService
{
public:
    RenderService(std::unique_ptr<BaseRenderFactory> renderFactory = std::make_unique<QtRenderFactory>());

    void render(const Scene &scene, BaseRenderSurface &surface) const;

private:
    std::unique_ptr<BaseRenderFactory> _renderFactory;
};
