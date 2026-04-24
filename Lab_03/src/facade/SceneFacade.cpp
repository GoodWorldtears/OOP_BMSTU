#include "facade/SceneFacade.h"

SceneFacade::SceneFacade(SceneManager &scene,
                         LoadService &load,
                         TransformService &transform,
                         RenderService &render)
    : _sceneManager(scene), _loadService(load), _transformService(transform), _renderService(render)
{
}

void SceneFacade::Execute(BaseCommand &command)
{
    command.execute(*this);
}

SceneManager &SceneFacade::sceneManager() { return _sceneManager; }
LoadService &SceneFacade::loadService() { return _loadService; }
TransformService &SceneFacade::transformService() { return _transformService; }
RenderService &SceneFacade::renderService() { return _renderService; }
