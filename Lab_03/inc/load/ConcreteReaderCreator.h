#pragma once

#include "load/BaseReaderCreator.h"
#include "load/CreatorConcepts.h"
#include <memory>

template <Derivative<BaseReader> TReader>
requires NotAbstract<TReader>
class ConcreteReaderCreator : public BaseReaderCreator
{
public:
    std::unique_ptr<BaseReader> createReader() const override
    {
        return std::make_unique<TReader>();
    }
};

class ReaderCreatorMaker
{
public:
    template <Derivative<BaseReader> TReader>
    requires NotAbstract<TReader>
    static std::unique_ptr<BaseReaderCreator> createReaderCreator()
    {
        return std::make_unique<ConcreteReaderCreator<TReader>>();
    }
};
