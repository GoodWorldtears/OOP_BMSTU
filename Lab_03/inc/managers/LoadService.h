#pragma once

#include "load/ReaderSolution.h"
#include "load/DirectorSolution.h"
#include "scene/BaseModel.h"
#include <memory>
#include <string>

class LoadService
{
public:
    enum class FileType { Txt, Csv };
    enum class StructureType { List };

    LoadService(ReaderSolution &readerSolution,
                DirectorSolution &directorSolution);

    std::shared_ptr<VisibleObject> loadModel(const std::string &path,
                                             FileType fileType,
                                             StructureType structureType) const;
private:
    ReaderSolution &_readerSolution;
    DirectorSolution &_directorSolution;
};
