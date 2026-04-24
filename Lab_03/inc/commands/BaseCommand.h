#pragma once

class SceneFacade;

class BaseCommand
{
public:
    virtual ~BaseCommand() = default;
    virtual void execute(SceneFacade &facade) = 0;
};
