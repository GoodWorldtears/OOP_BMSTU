#include "Dependencies/LoadDependencies.h"
#include "managers/LoadService.h"

LoadDependencies::LoadDependencies()
{
    _readerSolution.registrate(static_cast<int>(LoadService::FileType::Txt), &LoadDependencies::createTxtReaderCreator);
    _readerSolution.registrate(static_cast<int>(LoadService::FileType::Csv), &LoadDependencies::createCsvReaderCreator);

    _directorSolution.registrate(static_cast<int>(LoadService::StructureType::List), []()
    {
        return LoadDependencies::createListDirector();
    });
}

ReaderSolution &LoadDependencies::getReaderSolution() { return _readerSolution; }
DirectorSolution &LoadDependencies::getDirectorSolution() { return _directorSolution; }

std::unique_ptr<BaseReaderCreator> LoadDependencies::createTxtReaderCreator()
{
    return ReaderCreatorMaker::createReaderCreator<TxtModelReader>();
}

std::unique_ptr<BaseReaderCreator> LoadDependencies::createCsvReaderCreator()
{
    return ReaderCreatorMaker::createReaderCreator<CsvModelReader>();
}

std::unique_ptr<BaseDirector> LoadDependencies::createListDirector()
{
    auto builderCreator = BuilderCreatorMaker::createBuilderCreator<ListModelBuilder>();
    auto directorCreator = DirectorCreatorMaker::createDirectorCreator<BoneModelDirector, ListModelBuilder>();
    return directorCreator->createDirector(builderCreator->createBuilder());
}
