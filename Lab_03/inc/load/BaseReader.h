#pragma once

#include "load/ModelData.h"
#include <string>

class BaseReader
{
public:
    virtual ~BaseReader() = default;
    virtual ModelData read(const std::string &path) const = 0;
};
