#include "load/BoneModelDirector.h"
#include "load/BoneModelBuilder.h"

BoneModelDirector::BoneModelDirector(std::unique_ptr<BoneModelBuilder> builder)
    : _builder(std::move(builder))
{
}

std::shared_ptr<VisibleObject> BoneModelDirector::construct(const ModelData &data) const
{
    return _builder->build(data);
}
