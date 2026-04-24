#pragma once

#include "managers/LoadService.h"
#include "managers/SceneManager.h"
#include "managers/TransformService.h"
#include "managers/DrawerService.h"
#include "commands/BaseCommand.h"

class SceneFacade
{
public:
    SceneFacade() = delete;
    SceneFacade(SceneManager &scene,
                LoadService &load,
                TransformService &transform,
                RenderService &render);
    ~SceneFacade() = default;

    void Execute(BaseCommand &command);

    SceneManager &sceneManager();
    LoadService &loadService();
    TransformService &transformService();
    RenderService &renderService();

private:
    SceneManager &_sceneManager;
    LoadService &_loadService;
    TransformService &_transformService;
    RenderService &_renderService;
};
