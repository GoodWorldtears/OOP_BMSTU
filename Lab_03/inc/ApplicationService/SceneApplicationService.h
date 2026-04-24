#pragma once

#include "facade/SceneFacade.h"
#include "commands/BaseCommand.h"
#include <QString>
#include <vector>

class BaseRenderSurface;

class SceneApplicationService
{
public:
    explicit SceneApplicationService(SceneFacade &facade);

    void Execute(BaseCommand &command);
    void LoadModel(const QString &path, bool isTxt);
    void Draw(BaseRenderSurface &surface);

    void AddCamera(double x, double y, double z);
    void RemoveCamera(int index);
    void SetCamera(int index);

    void MoveSelectedModels(const std::vector<int> &indices, double dx, double dy, double dz);
    void RotateSelectedModels(const std::vector<int> &indices, double ax, double ay, double az);
    void ScaleSelectedModels(const std::vector<int> &indices, double kx, double ky, double kz);
    void RemoveSelectedModels(const std::vector<int> &indices);
    void CompositeSelectedModels(const std::vector<int> &indices, const QString &compositeName);

    const Scene &scene() const;

private:
    SceneFacade &_facade;
};
