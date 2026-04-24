#include "scene/BaseModel.h"
#include "scene/BaseBoneModel.h"
#include "render/Visitor.h"
#include "transform/TransformVisitor.h"

void BaseModel::accept(Visitor &visitor)
{
    visitor.visit(static_cast<BaseBoneModel &>(*this));
}

void BaseModel::accept(TransformVisitor &visitor)
{
    visitor.visit(static_cast<BaseBoneModel &>(*this));
}
