#include "scene/BaseBoneModel.h"

BaseBoneModel::BaseBoneModel(QString name, ModelStructurePtr structure)
    : BaseModel(std::move(name)), _structure(std::move(structure))
{
}
