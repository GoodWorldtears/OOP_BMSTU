#pragma once

class BaseBoneModel;
class Composite;
class Camera;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(BaseBoneModel &model) = 0;
    virtual void visit(Composite &composite) = 0;
    virtual void visit(Camera &camera) = 0;
};
