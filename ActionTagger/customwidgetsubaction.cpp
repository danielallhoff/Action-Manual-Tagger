#include "customwidgetsubaction.h"

CustomWidgetSubaction::CustomWidgetSubaction(QSet<QString> behaviours, Type type, int id, int initFrame) : CustomWidget(behaviours, type, id, initFrame)
{
    scrollerLast = new QSlider(Qt::Horizontal, 0);
    alignButtonLast = new QPushButton();
    QColor* color = getColor(type);
    scrollerLast->setStyleSheet(QString("QSlider::handle:horizontal {background-color: %1;}").arg(color->name()));
    scrollerLast->setValue(initFrame);
    setWidget(1,1, scrollerLast);
    setWidget(1,2,alignButtonLast);

    alignButtonLast->setText("Align");
    alignButtonLast->setFixedWidth(50);

    connect(scrollerLast,SIGNAL(valueChanged(int)), (CustomWidget*)this, SLOT(changed()));
    connect(alignButtonLast, SIGNAL(clicked()), this, SLOT(update_last()));
}

void CustomWidgetSubaction::update_last(){
    emit adjustScroller(scrollerLast);
}

void CustomWidgetSubaction::setPrecision(int value){
    CustomWidget::setPrecision(value);
    this->scrollerLast->setMaximum(value);
}
