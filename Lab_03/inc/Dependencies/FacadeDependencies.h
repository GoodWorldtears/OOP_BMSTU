#pragma once

#include "Dependencies/LoadDependencies.h"
#include "Dependencies/SceneDependencies.h"
#include "managers/DrawerService.h"
#include "managers/LoadService.h"
#include "managers/SceneManager.h"
#include "managers/TransformService.h"

class FacadeDependencies
{
public:
    FacadeDependencies();

    RenderService &getRenderService();
    LoadService &getLoadService();
    SceneManager &getSceneManager();
    TransformService &getTransformService();

private:
    LoadDependencies _loadDependencies;
    SceneDependencies _sceneDependencies;
    RenderService _renderService;
    LoadService _loadService;
    SceneManager _sceneManager;
    TransformService _transformService;
};
