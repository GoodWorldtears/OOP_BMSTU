#pragma once

#include "scene/Scene.h"
#include <memory>

class SceneDependencies
{
public:
    SceneDependencies();

    std::shared_ptr<Scene> createBaseScene() const;
};
