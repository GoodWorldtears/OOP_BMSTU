#pragma once

#include <cstddef>

class Edge
{
public:
    Edge() = default;
    Edge(std::size_t firstIndex, std::size_t secondIndex) : _first(firstIndex), _second(secondIndex) {}

    std::size_t first() const { return _first; }
    std::size_t second() const { return _second; }

private:
    std::size_t _first {0};
    std::size_t _second {0};
};
