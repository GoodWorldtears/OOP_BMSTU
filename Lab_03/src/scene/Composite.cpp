#include "scene/Composite.h"
#include "render/Visitor.h"
#include "transform/TransformVisitor.h"

Composite::Composite(QString name) : TransformableObject(std::move(name)) {}

void Composite::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void Composite::accept(TransformVisitor &visitor)
{
    visitor.visit(*this);
}

void Composite::add(const ObjectPtr &object)
{
    _objects.push_back(object);
}
