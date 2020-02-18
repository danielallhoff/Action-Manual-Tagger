#include "customwidgetsubaction.h"

CustomWidgetSubaction::CustomWidgetSubaction(QSet<QString> behaviours, Type type, int id, int initFrame) : CustomWidget(behaviours, type, id, initFrame)
{
    scrollerLast = new MyQSlider(Qt::Horizontal, nullptr);
    alignButtonLast = new QPushButton();
    QColor* color = getColor(type);
    scrollerLast->setStyleSheet(QString("QSlider::handle:horizontal {background-color: %1;}").arg(color->name()));
    scrollerLast->setValue(initFrame);

	alignButtonLast->setText("Align");
	alignButtonLast->setFixedWidth(50);

    QString id_text = QString::number(id);

    QWidget *spacing_widget = new QWidget();
    spacing_widget->setFixedWidth(80);
    //spacing_widget->setHidden(true);
	horizontal = new QHBoxLayout();
    horizontal->addWidget(spacing_widget);
	horizontal->addWidget(scrollerLast);
	horizontal->addWidget(alignButtonLast);
	
    QWidget *horizontal_widget = new QWidget;
    horizontal_widget->setLayout(horizontal);

    addWidgetVertical(horizontal_widget);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
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
