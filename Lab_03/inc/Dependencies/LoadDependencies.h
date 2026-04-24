#pragma once

#include "load/ConcreteReaderCreator.h"
#include "load/ConcreteDirectorCreator.h"
#include "load/ConcreteBuilderCreator.h"
#include "load/ReaderSolution.h"
#include "load/DirectorSolution.h"
#include "load/TxtModelReader.h"
#include "load/CsvModelReader.h"
#include "load/BoneModelDirector.h"
#include "load/ListModelBuilder.h"

class LoadDependencies
{
public:
    LoadDependencies();

    ReaderSolution &getReaderSolution();
    DirectorSolution &getDirectorSolution();

private:
    ReaderSolution _readerSolution;
    DirectorSolution _directorSolution;

    static std::unique_ptr<BaseReaderCreator> createTxtReaderCreator();
    static std::unique_ptr<BaseReaderCreator> createCsvReaderCreator();
    static std::unique_ptr<BaseDirector> createListDirector();
};
