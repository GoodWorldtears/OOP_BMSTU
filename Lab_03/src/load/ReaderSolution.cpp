#include "load/ReaderSolution.h"
#include <stdexcept>

ReaderSolution::ReaderSolution(std::initializer_list<std::pair<const int, CreateReaderCreator>> list)
    : _callbacks(list)
{
}

bool ReaderSolution::registrate(int id, CreateReaderCreator createFun)
{
    return _callbacks.emplace(id, createFun).second;
}

bool ReaderSolution::check(int id)
{
    return _callbacks.erase(id) == 1;
}

std::unique_ptr<BaseReaderCreator> ReaderSolution::create(int id) const
{
    const auto it = _callbacks.find(id);
    if (it == _callbacks.end())
        throw std::runtime_error("Неизвестный тип reader creator");

    return it->second();
}

std::unique_ptr<BaseReader> ReaderSolution::createReader(int fileType) const
{
    auto creator = create(fileType);
    return creator->createReader();
}
