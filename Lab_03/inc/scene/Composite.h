#pragma once

#include "scene/TransformableObject.h"
#include <vector>

class Composite : public TransformableObject
{
public:
    explicit Composite(QString name = "Composite");

    bool isVisible() const override { return true; }
    void accept(Visitor &visitor) override;
    void accept(TransformVisitor &visitor) override;

    void add(const ObjectPtr &object);
    const std::vector<ObjectPtr> &objects() const { return _objects; }

private:
    std::vector<ObjectPtr> _objects;
};
