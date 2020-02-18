#ifndef CUSTOMWIDGETSUBACTION_H
#define CUSTOMWIDGETSUBACTION_H

#include "customwidget.h"

class CustomWidgetSubaction : public CustomWidget
{
    Q_OBJECT
	QHBoxLayout *horizontal;
    MyQSlider *scrollerLast;
    QPushButton *alignButtonLast;
public:
    CustomWidgetSubaction();
    CustomWidgetSubaction(QSet<QString> behaviours, Type type, int id, int initFrame);
    int getLastFrame(){return scrollerLast->value();}
    void setPrecision(int value);
signals:

public slots:
    void update_last();
};

#endif // CUSTOMWIDGETSUBACTION_H
