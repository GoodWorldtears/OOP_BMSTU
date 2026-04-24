#include "ApplicationService/SceneApplicationService.h"
#include "commands/LoadCommands.h"
#include "commands/DrawCommands.h"
#include "commands/CameraCommands.h"
#include "commands/ModelCommands.h"
#include <QFileInfo>
#include "render/BaseRenderSurface.h"
#include <stdexcept>

SceneApplicationService::SceneApplicationService(SceneFacade &facade) : _facade(facade)
{
}

void SceneApplicationService::LoadModel(const QString &path, bool isTxt)
{
    if (path.isEmpty())
        throw std::invalid_argument("Путь к файлу не задан");

    QFileInfo fileInfo(path);
    if (!fileInfo.exists() || !fileInfo.isFile())
        throw std::invalid_argument("Файл не существует");

    const QString extension = fileInfo.suffix().toLower();
    if (isTxt && extension != "txt")
        throw std::invalid_argument("Ожидался файл формата .txt");
    if (!isTxt && extension != "csv")
        throw std::invalid_argument("Ожидался файл формата .csv");

    const auto fileType = isTxt ? LoadService::FileType::Txt : LoadService::FileType::Csv;
    LoadModelCommand command(path.toStdString(), fileType, LoadService::StructureType::List);
    _facade.Execute(command);
}

void SceneApplicationService::Execute(BaseCommand &command)
{
    _facade.Execute(command);
}

void SceneApplicationService::Draw(BaseRenderSurface &surface)
{
    DrawSceneCommand command(surface);
    _facade.Execute(command);
}

void SceneApplicationService::AddCamera(double x, double y, double z)
{
    AddCameraCommand command({x, y, z});
    _facade.Execute(command);
}

void SceneApplicationService::RemoveCamera(int index)
{
    RemoveCameraCommand command(index);
    _facade.Execute(command);
}

void SceneApplicationService::SetCamera(int index)
{
    SetCameraCommand command(index);
    _facade.Execute(command);
}

void SceneApplicationService::MoveSelectedModels(const std::vector<int> &indices, double dx, double dy, double dz)
{
    MoveModelCommand command(indices, {dx, dy, dz});
    _facade.Execute(command);
}

void SceneApplicationService::RotateSelectedModels(const std::vector<int> &indices, double ax, double ay, double az)
{
    RotateModelCommand command(indices, {ax, ay, az});
    _facade.Execute(command);
}

void SceneApplicationService::ScaleSelectedModels(const std::vector<int> &indices, double kx, double ky, double kz)
{
    ScaleModelCommand command(indices, {kx, ky, kz});
    _facade.Execute(command);
}

void SceneApplicationService::RemoveSelectedModels(const std::vector<int> &indices)
{
    RemoveModelCommand command(indices);
    _facade.Execute(command);
}

void SceneApplicationService::CompositeSelectedModels(const std::vector<int> &indices, const QString &compositeName)
{
    CompositeModelCommand command(indices, compositeName);
    _facade.Execute(command);
}

const Scene &SceneApplicationService::scene() const
{
    return _facade.sceneManager().scene();
}
