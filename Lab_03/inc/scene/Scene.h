#pragma once

#include "scene/AbstractObject.h"
#include "scene/Camera.h"
#include "scene/Composite.h"
#include <vector>
#include <memory>

class Scene
{
public:
    void addObject(const ObjectPtr &object);
    void removeObject(int index);
    void clear();

    int objectCount() const;
    const std::vector<ObjectPtr> &objects() const;
    ObjectPtr objectAt(int index) const;

    std::shared_ptr<Camera> cameraAt(int index) const;
    int cameraCount() const;
    std::vector<std::shared_ptr<Camera>> cameras() const;

    void setActiveCameraIndex(int index);
    int activeCameraIndex() const { return _activeCameraIndex; }
    std::shared_ptr<Camera> activeCamera() const;

private:
    std::vector<ObjectPtr> _objects;
    int _activeCameraIndex {0};
};
