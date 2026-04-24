#include "Dependencies/FacadeDependencies.h"

FacadeDependencies::FacadeDependencies()
    : _loadService(_loadDependencies.getReaderSolution(),
                   _loadDependencies.getDirectorSolution()),
      _sceneManager(_sceneDependencies.createBaseScene())
{
}

RenderService &FacadeDependencies::getRenderService() { return _renderService; }
LoadService &FacadeDependencies::getLoadService() { return _loadService; }
SceneManager &FacadeDependencies::getSceneManager() { return _sceneManager; }
TransformService &FacadeDependencies::getTransformService() { return _transformService; }
