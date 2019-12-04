#ifndef INTERVAL_H
#define INTERVAL_H


#include "Type.h"
class Interval
{
public:
    Interval();
    Interval(QString name, int initFrame, int lastFrame, Type type, Interval* father);

    void setName(QString name){this->name = name;}

    QString getName() const;

    int getInitFrame() const;
    void setInitFrame(int value);

    int getLastFrame() const;
    void setLastFrame(int value);


    Interval *getFather() const;
    void setFather(Interval *value);

    Type getType() const;
    void setType(const Type &value);

private:
    QString name;
    int initFrame;
    int lastFrame;
    //Action :0 , subaction:1, subsubaction:2 ....etc
    Type type;
    Interval *father;

};

#endif // INTERVAL_H
