#pragma once

#include "load/BaseReader.h"
#include <memory>

class BaseReaderCreator
{
public:
    virtual ~BaseReaderCreator() = default;
    virtual std::unique_ptr<BaseReader> createReader() const = 0;
};
