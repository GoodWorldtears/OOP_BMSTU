#include "render/QtRenderFactory.h"
#include "render/QtRenderSurface.h"
#include "render/QtDrawer.h"
#include <stdexcept>

std::unique_ptr<BaseDrawer> QtRenderFactory::createDrawer(BaseRenderSurface &surface) const
{
    auto *qtSurface = dynamic_cast<QtRenderSurface *>(&surface);
    if (!qtSurface)
        throw std::runtime_error("Неподдерживаемая поверхность рендера для Qt");

    return std::make_unique<QtDrawer>(qtSurface->scene());
}
