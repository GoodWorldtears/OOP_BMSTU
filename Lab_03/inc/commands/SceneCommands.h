#pragma once

#include "commands/BaseCommand.h"

class BaseSceneCommand : public BaseCommand
{
};

class ClearSceneCommand : public BaseSceneCommand
{
public:
    void execute(SceneFacade &facade) override;
};
