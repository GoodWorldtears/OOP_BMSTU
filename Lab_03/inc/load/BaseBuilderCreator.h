#pragma once

#include "load/BaseBuilder.h"
#include <memory>

class BaseBuilderCreator
{
public:
    virtual ~BaseBuilderCreator() = default;
    virtual std::unique_ptr<BaseBuilder> createBuilder() const = 0;
};
