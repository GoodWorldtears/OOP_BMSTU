#include "load/ListModelBuilder.h"
#include "scene/BaseBoneModel.h"
#include "scene/ListModelStructure.h"

std::shared_ptr<VisibleObject> ListModelBuilder::build(const ModelData &data) const
{
    auto structure = std::make_shared<ListModelStructure>(data.points, data.edges);
    return std::make_shared<BaseBoneModel>(data.name, structure);
}
