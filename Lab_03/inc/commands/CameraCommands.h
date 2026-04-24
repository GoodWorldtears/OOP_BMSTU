#pragma once

#include "commands/BaseCommand.h"
#include "math/Vector3D.h"

class BaseCameraCommand : public BaseCommand
{
public:
    BaseCameraCommand() = default;
};

class AddCameraCommand : public BaseCameraCommand
{
public:
    explicit AddCameraCommand(Vector3D position);
    void execute(SceneFacade &facade) override;
private:
    Vector3D _position;
};

class RemoveCameraCommand : public BaseCameraCommand
{
public:
    explicit RemoveCameraCommand(int index);
    void execute(SceneFacade &facade) override;
private:
    int _index {-1};
};

class SetCameraCommand : public BaseCameraCommand
{
public:
    explicit SetCameraCommand(int index);
    void execute(SceneFacade &facade) override;
private:
    int _index {-1};
};
