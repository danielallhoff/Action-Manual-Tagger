#include "interval.h"

Interval::Interval()
{
    name = "";
    initFrame = -1;
    lastFrame = -1;
    type = BEHAVIOUR;
    father = nullptr;
}


Interval::Interval(QString name, int initFrame, int lastFrame, Type type, Interval* father){
    this->name = name;
    this->initFrame = initFrame;
    this->lastFrame = lastFrame;
    this->type = type;
    this->father = father;
}

QString Interval::getName() const
{
    return name;
}

int Interval::getInitFrame() const
{
    return initFrame;
}

void Interval::setInitFrame(int value)
{
    initFrame = value;
}

int Interval::getLastFrame() const
{
    return lastFrame;
}

void Interval::setLastFrame(int value)
{
    lastFrame = value;
}


Interval *Interval::getFather() const
{
    return father;
}

void Interval::setFather(Interval *value)
{
    father = value;
}

Type Interval::getType() const
{
    return type;
}

void Interval::setType(const Type &value)
{
    type = value;
}
