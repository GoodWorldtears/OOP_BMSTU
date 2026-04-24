#include "Dependencies/SceneDependencies.h"

SceneDependencies::SceneDependencies() = default;

std::shared_ptr<Scene> SceneDependencies::createBaseScene() const
{
    return std::make_shared<Scene>();
}
