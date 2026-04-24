#include "load/DirectorSolution.h"
#include <stdexcept>

DirectorSolution::DirectorSolution(std::initializer_list<std::pair<const int, CreateDirectorCallback>> list)
    : _callbacks(list)
{
}

bool DirectorSolution::registrate(int id, CreateDirectorCallback createFun)
{
    return _callbacks.emplace(id, std::move(createFun)).second;
}

bool DirectorSolution::check(int id)
{
    return _callbacks.erase(id) == 1;
}

std::unique_ptr<BaseDirector> DirectorSolution::create(int id) const
{
    const auto it = _callbacks.find(id);
    if (it == _callbacks.end())
        throw std::runtime_error("Неизвестный тип director");

    return it->second();
}

std::unique_ptr<BaseDirector> DirectorSolution::createDirector(int structureType) const
{
    return create(structureType);
}
