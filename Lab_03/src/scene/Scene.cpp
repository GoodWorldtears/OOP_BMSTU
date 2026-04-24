#include "scene/Scene.h"
#include <stdexcept>

void Scene::addObject(const ObjectPtr &object)
{
    _objects.push_back(object);
}

void Scene::removeObject(int index)
{
    if (index < 0 || index >= static_cast<int>(_objects.size()))
        throw std::out_of_range("Некорректный индекс объекта");
    _objects.erase(_objects.begin() + index);
    if (_activeCameraIndex >= cameraCount())
        _activeCameraIndex = cameraCount() == 0 ? 0 : cameraCount() - 1;
}

void Scene::clear()
{
    _objects.clear();
    _activeCameraIndex = 0;
}

int Scene::objectCount() const
{
    return static_cast<int>(_objects.size());
}

const std::vector<ObjectPtr> &Scene::objects() const
{
    return _objects;
}

ObjectPtr Scene::objectAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(_objects.size()))
        throw std::out_of_range("Некорректный индекс объекта");
    return _objects.at(index);
}

std::shared_ptr<Camera> Scene::cameraAt(int index) const
{
    const auto cameraList = cameras();
    if (index < 0 || index >= static_cast<int>(cameraList.size()))
        throw std::out_of_range("Некорректный индекс камеры");
    return cameraList.at(index);
}

int Scene::cameraCount() const
{
    return static_cast<int>(cameras().size());
}

std::vector<std::shared_ptr<Camera>> Scene::cameras() const
{
    std::vector<std::shared_ptr<Camera>> result;
    for (const auto &object : _objects)
    {
        auto camera = std::dynamic_pointer_cast<Camera>(object);
        if (camera)
            result.push_back(camera);
    }
    return result;
}

void Scene::setActiveCameraIndex(int index)
{
    if (index < 0 || index >= cameraCount())
        throw std::out_of_range("Некорректный индекс камеры");
    _activeCameraIndex = index;
}

std::shared_ptr<Camera> Scene::activeCamera() const
{
    const auto cameraList = cameras();
    if (cameraList.empty())
        return nullptr;
    const int safeIndex = std::max(0, std::min(_activeCameraIndex, static_cast<int>(cameraList.size()) - 1));
    return cameraList.at(safeIndex);
}
