#pragma once

#include "load/BaseDirector.h"
#include <memory>

class BoneModelBuilder;

class BoneModelDirector : public BaseDirector
{
public:
    explicit BoneModelDirector(std::unique_ptr<BoneModelBuilder> builder);
    ~BoneModelDirector() override = default;

    std::shared_ptr<VisibleObject> construct(const ModelData &data) const override;

private:
    std::unique_ptr<BoneModelBuilder> _builder;
};
