#pragma once

#include "math/Vector3D.h"
#include <memory>
#include <QString>

class Visitor;

class AbstractObject
{
public:
    explicit AbstractObject(QString name = "Object") : _name(std::move(name)) {}
    virtual ~AbstractObject() = default;

    virtual bool isVisible() const = 0;
    virtual void accept(Visitor &visitor) = 0;

    const QString &name() const { return _name; }
    void setName(QString name) { _name = std::move(name); }

private:
    QString _name;
};

using ObjectPtr = std::shared_ptr<AbstractObject>;
