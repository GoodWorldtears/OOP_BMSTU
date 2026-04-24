#pragma once

#include "load/BoneModelReader.h"
#include <string>

class CsvModelReader : public BoneModelReader
{
public:
    ModelData read(const std::string &path) const override;
};
