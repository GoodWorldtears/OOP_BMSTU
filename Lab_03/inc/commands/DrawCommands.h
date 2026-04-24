#pragma once

#include "commands/BaseCommand.h"

class BaseRenderSurface;

class BaseDrawCommand : public BaseCommand
{
public:
    explicit BaseDrawCommand(BaseRenderSurface &surface) : _surface(surface) {}
protected:
    BaseRenderSurface &_surface;
};

class DrawSceneCommand : public BaseDrawCommand
{
public:
    explicit DrawSceneCommand(BaseRenderSurface &surface);
    void execute(SceneFacade &facade) override;
};
