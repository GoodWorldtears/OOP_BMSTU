#include "commands/CameraCommands.h"
#include "facade/SceneFacade.h"
#include "scene/Camera.h"

AddCameraCommand::AddCameraCommand(Vector3D position) : _position(position) {}
RemoveCameraCommand::RemoveCameraCommand(int index) : _index(index) {}
SetCameraCommand::SetCameraCommand(int index) : _index(index) {}

void AddCameraCommand::execute(SceneFacade &facade)
{
    const int number = facade.sceneManager().scene().cameraCount() + 1;
    facade.sceneManager().scene().addObject(std::make_shared<Camera>(_position, QString("Camera %1").arg(number)));
}

void RemoveCameraCommand::execute(SceneFacade &facade)
{
    auto camera = facade.sceneManager().scene().cameraAt(_index);
    const auto &objects = facade.sceneManager().scene().objects();
    for (int i = 0; i < static_cast<int>(objects.size()); ++i)
    {
        if (objects[i] == camera)
        {
            facade.sceneManager().scene().removeObject(i);
            return;
        }
    }
}

void SetCameraCommand::execute(SceneFacade &facade)
{
    facade.sceneManager().scene().setActiveCameraIndex(_index);
}
