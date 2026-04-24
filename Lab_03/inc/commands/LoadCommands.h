#pragma once

#include "commands/BaseCommand.h"
#include "managers/LoadService.h"
#include <string>

class BaseLoadCommand : public BaseCommand
{
public:
    BaseLoadCommand(std::string path, LoadService::FileType fileType, LoadService::StructureType structureType);
protected:
    std::string _path;
    LoadService::FileType _fileType;
    LoadService::StructureType _structureType;
};

class LoadModelCommand : public BaseLoadCommand
{
public:
    LoadModelCommand(std::string path, LoadService::FileType fileType, LoadService::StructureType structureType);
    void execute(SceneFacade &facade) override;
};
