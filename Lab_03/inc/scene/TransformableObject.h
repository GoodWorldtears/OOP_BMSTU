#pragma once

#include "scene/AbstractObject.h"

class TransformVisitor;

class TransformableObject : public AbstractObject
{
public:
    using AbstractObject::AbstractObject;
    virtual void accept(TransformVisitor &visitor) = 0;
};
