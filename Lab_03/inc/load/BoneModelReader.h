#pragma once

#include "load/BaseReader.h"
#include <string>

class BoneModelReader : public BaseReader
{
protected:
    static QString baseNameFromPath(const std::string &path);
};
