#pragma once

#include "load/BaseDirectorCreator.h"
#include "load/CreatorConcepts.h"
#include <memory>
#include <stdexcept>
#include <type_traits>

template <Derivative<BaseDirector> TDirector, Derivative<BaseBuilder> TBuilder>
requires NotAbstract<TDirector> && NotAbstract<TBuilder>
class ConcreteDirectorCreator : public BaseDirectorCreator
{
public:
    std::unique_ptr<BaseDirector> createDirector(std::unique_ptr<BaseBuilder> builder) const override
    {
        auto *rawBuilder = dynamic_cast<TBuilder *>(builder.get());
        if (!rawBuilder)
            throw std::runtime_error("Передан builder неподходящего типа для director");

        builder.release();
        std::unique_ptr<TBuilder> concreteBuilder(rawBuilder);
        return std::make_unique<TDirector>(std::move(concreteBuilder));
    }
};

class DirectorCreatorMaker
{
public:
    template <Derivative<BaseDirector> TDirector, Derivative<BaseBuilder> TBuilder>
    requires NotAbstract<TDirector> && NotAbstract<TBuilder>
    static std::unique_ptr<BaseDirectorCreator> createDirectorCreator()
    {
        return std::make_unique<ConcreteDirectorCreator<TDirector, TBuilder>>();
    }
};
