#include "commands/LoadCommands.h"
#include "facade/SceneFacade.h"

BaseLoadCommand::BaseLoadCommand(std::string path, LoadService::FileType fileType, LoadService::StructureType structureType)
    : _path(std::move(path)), _fileType(fileType), _structureType(structureType)
{
}

LoadModelCommand::LoadModelCommand(std::string path, LoadService::FileType fileType, LoadService::StructureType structureType)
    : BaseLoadCommand(std::move(path), fileType, structureType)
{
}

void LoadModelCommand::execute(SceneFacade &facade)
{
    auto model = facade.loadService().loadModel(_path, _fileType, _structureType);
    facade.sceneManager().scene().addObject(model);
}
