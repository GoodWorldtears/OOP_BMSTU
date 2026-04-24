#pragma once

#include "load/BaseBuilderCreator.h"
#include "load/CreatorConcepts.h"
#include <memory>

template <Derivative<BaseBuilder> TBuilder>
requires NotAbstract<TBuilder>
class ConcreteBuilderCreator : public BaseBuilderCreator
{
public:
    std::unique_ptr<BaseBuilder> createBuilder() const override
    {
        return std::make_unique<TBuilder>();
    }
};

class BuilderCreatorMaker
{
public:
    template <Derivative<BaseBuilder> TBuilder>
    requires NotAbstract<TBuilder>
    static std::unique_ptr<BaseBuilderCreator> createBuilderCreator()
    {
        return std::make_unique<ConcreteBuilderCreator<TBuilder>>();
    }
};
