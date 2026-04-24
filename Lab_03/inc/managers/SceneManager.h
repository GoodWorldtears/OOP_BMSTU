#pragma once

#include "scene/Scene.h"
#include <memory>
#include <vector>

class SceneManager
{
public:
    SceneManager() = default;
    explicit SceneManager(std::shared_ptr<Scene> baseScene);

    Scene &scene();
    const Scene &scene() const;

    std::shared_ptr<Scene> scenePtr() const;
    std::shared_ptr<Scene> sceneAt(int index) const;
    int sceneCount() const;

    void addScene(const std::shared_ptr<Scene> &scene);
    void removeScene(int index);
    void setActiveScene(int index);
    int activeSceneIndex() const;

private:
    std::vector<std::shared_ptr<Scene>> _scenes;
    int _activeSceneIndex {0};
};
