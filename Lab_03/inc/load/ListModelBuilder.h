#pragma once

#include "load/BoneModelBuilder.h"

class ListModelBuilder : public BoneModelBuilder
{
public:
    std::shared_ptr<VisibleObject> build(const ModelData &data) const override;
};
