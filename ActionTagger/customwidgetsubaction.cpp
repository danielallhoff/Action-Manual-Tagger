#include "customwidgetsubaction.h"

CustomWidgetSubaction::CustomWidgetSubaction(QSet<QString> behaviours, Type type, int id, int initFrame) : CustomWidget(behaviours, type, id, initFrame)
{
    scrollerLast = new QSlider(Qt::Horizontal, 0);
    QColor* color = getColor(type);
    scrollerLast->setStyleSheet(QString("QSlider::handle:horizontal {background-color: %1;}").arg(color->name()));
    scrollerLast->setValue(initFrame);
    setWidget(1,1, scrollerLast);

    connect(scrollerLast,SIGNAL(valueChanged(int)), this, SLOT(changed()));
}


void CustomWidgetSubaction::setPrecision(int value){
    CustomWidget::setPrecision(value);
    this->scrollerLast->setMaximum(value);
}
