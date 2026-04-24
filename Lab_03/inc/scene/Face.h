#pragma once

#include <vector>
#include <cstddef>

class Face
{
public:
    Face() = default;
    explicit Face(std::vector<std::size_t> indices) : _indices(std::move(indices)) {}

    const std::vector<std::size_t> &indices() const { return _indices; }

private:
    std::vector<std::size_t> _indices;
};
