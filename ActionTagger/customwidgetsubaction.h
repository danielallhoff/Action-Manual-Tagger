#ifndef CUSTOMWIDGETSUBACTION_H
#define CUSTOMWIDGETSUBACTION_H

#include "customwidget.h"

class CustomWidgetSubaction : public CustomWidget
{
    QSlider *scrollerLast;
public:
    CustomWidgetSubaction();
    CustomWidgetSubaction(QSet<QString> behaviours, Type type, int id, int initFrame);
    int getLastFrame(){return scrollerLast->value();}
    void setPrecision(int value);
signals:
    void somethingChanged(QWidget*);
public slots:
    void changed();
};

#endif // CUSTOMWIDGETSUBACTION_H
