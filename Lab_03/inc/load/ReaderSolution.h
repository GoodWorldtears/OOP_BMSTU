#pragma once

#include "load/BaseReader.h"
#include "load/BaseReaderCreator.h"
#include <map>
#include <memory>

class ReaderSolution
{
public:
    using CreateReaderCreator = std::unique_ptr<BaseReaderCreator>(*)();
    using CallbackMap = std::map<int, CreateReaderCreator>;

public:
    ReaderSolution() = default;
    ReaderSolution(std::initializer_list<std::pair<const int, CreateReaderCreator>> list);

    bool registrate(int id, CreateReaderCreator createFun);
    bool check(int id);

    std::unique_ptr<BaseReaderCreator> create(int id) const;
    std::unique_ptr<BaseReader> createReader(int fileType) const;

private:
    CallbackMap _callbacks;
};
