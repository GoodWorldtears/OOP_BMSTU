#include "managers/LoadService.h"

LoadService::LoadService(ReaderSolution &readerSolution,
                         DirectorSolution &directorSolution)
    : _readerSolution(readerSolution), _directorSolution(directorSolution)
{
}

std::shared_ptr<VisibleObject> LoadService::loadModel(const std::string &path,
                                                      FileType fileType,
                                                      StructureType structureType) const
{
    const auto reader = _readerSolution.createReader(static_cast<int>(fileType));
    const auto data = reader->read(path);

    const auto director = _directorSolution.createDirector(static_cast<int>(structureType));
    return director->construct(data);
}
