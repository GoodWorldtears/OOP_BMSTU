#pragma once

#include "scene/TransformableObject.h"

class Visitor;
class TransformVisitor;

class BaseModel : public TransformableObject
{
public:
    using TransformableObject::TransformableObject;
    bool isVisible() const override { return true; }

    void accept(Visitor &visitor) override;
    void accept(TransformVisitor &visitor) override;
};

using VisibleObject = BaseModel;
