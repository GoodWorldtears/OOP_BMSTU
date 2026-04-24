#pragma once

class BaseBoneModel;
class Composite;

class TransformVisitor
{
public:
    virtual ~TransformVisitor() = default;
    virtual void visit(BaseBoneModel &model) = 0;
    virtual void visit(Composite &composite) = 0;
};
