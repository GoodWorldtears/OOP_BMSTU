#pragma once

#include "load/BaseDirector.h"
#include "load/BaseBuilderCreator.h"
#include "load/BaseDirectorCreator.h"
#include <functional>
#include <map>
#include <memory>

class DirectorSolution
{
public:
    using CreateDirectorCallback = std::function<std::unique_ptr<BaseDirector>()>;
    using CallbackMap = std::map<int, CreateDirectorCallback>;

public:
    DirectorSolution() = default;
    DirectorSolution(std::initializer_list<std::pair<const int, CreateDirectorCallback>> list);

    bool registrate(int id, CreateDirectorCallback createFun);
    bool check(int id);

    std::unique_ptr<BaseDirector> create(int id) const;
    std::unique_ptr<BaseDirector> createDirector(int structureType) const;

private:
    CallbackMap _callbacks;
};
