#pragma once

#include "commands/BaseCommand.h"
#include "math/Vector3D.h"
#include <vector>
#include <QString>

class BaseModelCommand : public BaseCommand
{
public:
    explicit BaseModelCommand(std::vector<int> indices);
protected:
    std::vector<int> _indices;
};

class MoveModelCommand : public BaseModelCommand
{
public:
    MoveModelCommand(std::vector<int> indices, Vector3D delta);
    void execute(SceneFacade &facade) override;
private:
    Vector3D _delta;
};

class RotateModelCommand : public BaseModelCommand
{
public:
    RotateModelCommand(std::vector<int> indices, Vector3D angles);
    void execute(SceneFacade &facade) override;
private:
    Vector3D _angles;
};

class ScaleModelCommand : public BaseModelCommand
{
public:
    ScaleModelCommand(std::vector<int> indices, Vector3D factors);
    void execute(SceneFacade &facade) override;
private:
    Vector3D _factors;
};

class RemoveModelCommand : public BaseModelCommand
{
public:
    explicit RemoveModelCommand(std::vector<int> indices);
    void execute(SceneFacade &facade) override;
};

class CompositeModelCommand : public BaseModelCommand
{
public:
    CompositeModelCommand(std::vector<int> indices, QString compositeName);
    void execute(SceneFacade &facade) override;
private:
    QString _compositeName;
};
