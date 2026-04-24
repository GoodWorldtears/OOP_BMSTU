#include "commands/ModelCommands.h"
#include "facade/SceneFacade.h"
#include "scene/TransformableObject.h"
#include "scene/Composite.h"
#include <algorithm>
#include <stdexcept>

BaseModelCommand::BaseModelCommand(std::vector<int> indices) : _indices(std::move(indices)) {}
MoveModelCommand::MoveModelCommand(std::vector<int> indices, Vector3D delta)
    : BaseModelCommand(std::move(indices)), _delta(delta) {}
RotateModelCommand::RotateModelCommand(std::vector<int> indices, Vector3D angles)
    : BaseModelCommand(std::move(indices)), _angles(angles) {}
ScaleModelCommand::ScaleModelCommand(std::vector<int> indices, Vector3D factors)
    : BaseModelCommand(std::move(indices)), _factors(factors) {}
RemoveModelCommand::RemoveModelCommand(std::vector<int> indices) : BaseModelCommand(std::move(indices)) {}
CompositeModelCommand::CompositeModelCommand(std::vector<int> indices, QString compositeName)
    : BaseModelCommand(std::move(indices)), _compositeName(std::move(compositeName)) {}

void MoveModelCommand::execute(SceneFacade &facade)
{
    for (int index : _indices)
    {
        auto object = std::dynamic_pointer_cast<TransformableObject>(facade.sceneManager().scene().objectAt(index));
        if (object)
            facade.transformService().move(*object, _delta);
    }
}

void RotateModelCommand::execute(SceneFacade &facade)
{
    for (int index : _indices)
    {
        auto object = std::dynamic_pointer_cast<TransformableObject>(facade.sceneManager().scene().objectAt(index));
        if (object)
            facade.transformService().rotate(*object, _angles);
    }
}

void ScaleModelCommand::execute(SceneFacade &facade)
{
    for (int index : _indices)
    {
        auto object = std::dynamic_pointer_cast<TransformableObject>(facade.sceneManager().scene().objectAt(index));
        if (object)
            facade.transformService().scale(*object, _factors);
    }
}

void RemoveModelCommand::execute(SceneFacade &facade)
{
    std::sort(_indices.begin(), _indices.end(), std::greater<>());
    for (int index : _indices)
        facade.sceneManager().scene().removeObject(index);
}

void CompositeModelCommand::execute(SceneFacade &facade)
{
    auto &scene = facade.sceneManager().scene();

    if (_indices.empty())
        throw std::invalid_argument("Не выбраны объекты для объединения");

    auto composite = std::make_shared<Composite>(_compositeName);
    std::vector<int> sorted = _indices;
    std::sort(sorted.begin(), sorted.end(), std::greater<>());

    for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
        composite->add(scene.objectAt(*it));

    for (int index : sorted)
        scene.removeObject(index);

    scene.addObject(composite);
}
