#include "managers/DrawerService.h"
#include "render/RenderVisitor.h"
#include "render/BaseRenderSurface.h"
#include "scene/Scene.h"

RenderService::RenderService(std::unique_ptr<BaseRenderFactory> renderFactory)
    : _renderFactory(std::move(renderFactory))
{
}

void RenderService::render(const Scene &scene, BaseRenderSurface &surface) const
{
    auto drawer = _renderFactory->createDrawer(surface);
    RenderVisitor visitor(std::move(drawer), scene);
    for (const auto &object : scene.objects())
    {
        if (object->isVisible())
            object->accept(visitor);
    }
}
