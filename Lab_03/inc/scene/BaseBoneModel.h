#pragma once

#include "scene/BaseModel.h"
#include "scene/ModelStructure.h"

class BaseBoneModel : public BaseModel
{
public:
    BaseBoneModel(QString name, ModelStructurePtr structure);

    ModelStructure &structure() { return *_structure; }
    const ModelStructure &structure() const { return *_structure; }


private:
    ModelStructurePtr _structure;
};
