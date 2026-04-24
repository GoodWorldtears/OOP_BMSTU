#include "managers/SceneManager.h"
#include <algorithm>
#include <stdexcept>

namespace
{
void validateSceneIndex(int index, int size)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Некорректный индекс сцены");
}
}

SceneManager::SceneManager(std::shared_ptr<Scene> baseScene)
{
    if (!baseScene)
        throw std::invalid_argument("Базовая сцена не задана");

    _scenes.push_back(std::move(baseScene));
}

Scene &SceneManager::scene()
{
    return *scenePtr();
}

const Scene &SceneManager::scene() const
{
    return *scenePtr();
}

std::shared_ptr<Scene> SceneManager::scenePtr() const
{
    if (_scenes.empty())
        throw std::runtime_error("Нет доступных сцен");

    validateSceneIndex(_activeSceneIndex, static_cast<int>(_scenes.size()));
    return _scenes.at(_activeSceneIndex);
}

std::shared_ptr<Scene> SceneManager::sceneAt(int index) const
{
    validateSceneIndex(index, static_cast<int>(_scenes.size()));
    return _scenes.at(index);
}

int SceneManager::sceneCount() const
{
    return static_cast<int>(_scenes.size());
}

void SceneManager::addScene(const std::shared_ptr<Scene> &scene)
{
    if (!scene)
        throw std::invalid_argument("Сцена не задана");

    _scenes.push_back(scene);
}

void SceneManager::removeScene(int index)
{
    validateSceneIndex(index, static_cast<int>(_scenes.size()));
    if (_scenes.size() == 1)
        throw std::runtime_error("Нельзя удалить последнюю сцену");

    _scenes.erase(_scenes.begin() + index);
    _activeSceneIndex = std::clamp(_activeSceneIndex, 0, static_cast<int>(_scenes.size()) - 1);
}

void SceneManager::setActiveScene(int index)
{
    validateSceneIndex(index, static_cast<int>(_scenes.size()));
    _activeSceneIndex = index;
}

int SceneManager::activeSceneIndex() const
{
    return _activeSceneIndex;
}
