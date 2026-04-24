#include "commands/DrawCommands.h"
#include "facade/SceneFacade.h"

DrawSceneCommand::DrawSceneCommand(BaseRenderSurface &surface) : BaseDrawCommand(surface) {}

void DrawSceneCommand::execute(SceneFacade &facade)
{
    facade.renderService().render(facade.sceneManager().scene(), _surface);
}
