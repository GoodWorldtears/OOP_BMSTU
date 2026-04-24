#pragma once

#include "render/BaseRenderFactory.h"
#include <memory>

class Scene;
class BaseRenderSurface;

class RenderService
{
public:
    explicit RenderService(std::unique_ptr<BaseRenderFactory> renderFactory);

    void render(const Scene &scene, BaseRenderSurface &surface) const;

private:
    std::unique_ptr<BaseRenderFactory> _renderFactory;
};
