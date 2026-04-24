#pragma once

#include "load/BaseDirector.h"
#include <memory>

class BaseBuilder;

class BaseDirectorCreator
{
public:
    virtual ~BaseDirectorCreator() = default;
    virtual std::unique_ptr<BaseDirector> createDirector(std::unique_ptr<BaseBuilder> builder) const = 0;
};
