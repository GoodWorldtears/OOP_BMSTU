#include "commands/SceneCommands.h"
#include "facade/SceneFacade.h"

void ClearSceneCommand::execute(SceneFacade &facade)
{
    facade.sceneManager().scene().clear();
}
