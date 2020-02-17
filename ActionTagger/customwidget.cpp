#include "customwidget.h"


CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

CustomWidget::CustomWidget(QSet<QString> behaviours, Type type, int id, int initFrame) {
    vertical = new QVBoxLayout();
    horizontal = new QHBoxLayout();
    scroller = new MyQSlider(Qt::Horizontal, 0);
    father = new QLabel();
    idLabel = new QLabel();
    drop_down_father = new QComboBox();
    drop_down_input = new QComboBox();
    alignButton = new QPushButton();

    QColor *color = new QColor();

    this->type = type;
    drop_down_input->setDuplicatesEnabled(false);
    //Set input
    for(QString item: behaviours){
        drop_down_father->addItem(item);
        drop_down_input->addItem(item);
    }

    color = getColor(type);

    scroller->setStyleSheet(QString("QSlider::handle:horizontal {background-color: %1;}").arg(color->name()));
    scroller->setValue(initFrame);
	
    alignButton->setText("Align");
    alignButton->setFixedWidth(50);

    //Hidden id
    QString id_text = QString::number(id);
    idLabel->setText(id_text);
    idLabel->setFixedWidth(1);
    idLabel->setHidden(true);

    drop_down_input->setStyleSheet(QString("QComboBox {color: %1;}").arg(color->name()));
    drop_down_input->setFixedWidth(80);

    //Grid layout
	horizontal->addWidget(drop_down_input);
	horizontal->addWidget(scroller);
	horizontal->addWidget(alignButton);
	horizontal->addWidget(idLabel);
	
	QWidget *horizontal_widget = new QWidget;
	horizontal_widget->setLayout(horizontal);
    vertical->addWidget(horizontal_widget);
    vertical->setSizeConstraint(QLayout::SetMinimumSize);
    this->setLayout(vertical);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    connect(scroller,SIGNAL(valueChanged(int)), this, SLOT(changed()));
    connect(drop_down_input,SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));
    connect(alignButton, SIGNAL(clicked()), this, SLOT(update()));
}

QColor* CustomWidget::getColor(Type type){
    QColor* color = new QColor();
    switch(type){
        case BEHAVIOUR:

            color->setRgb(255,0,0);
            break;
        case ACTION:

            color->setRgb(0,255,0);
            break;
        case SUBACTION:

            color->setRgb(0,0,255);
            break;
    }
    return color;
}

int CustomWidget::getFrame(){
    return scroller->value();
}

QString CustomWidget::getInput(){
    return drop_down_input->currentText();
}
QString CustomWidget::getFather(){
    return drop_down_father->currentText();
}

int CustomWidget::getId(){
    QString label = idLabel->text();
    return label.toInt();
}
void CustomWidget::changed(){
    emit somethingChanged(this);
}

void CustomWidget::update(){
    emit adjustScroller(scroller);
}

void CustomWidget::setPrecision(int value){
    this->scroller->setMaximum(value);
}

void CustomWidget::setId(int id){
    this->idLabel->setText(QString(id));
}

void CustomWidget::addWidgetVertical(QWidget* widget){
	vertical->addWidget(widget);
	
	
}

void CustomWidget::setInput(QString input){
    int index = drop_down_input->findText(input);
    this->drop_down_input->setCurrentIndex(index);
}
void CustomWidget::addInput(QString input){
    if(drop_down_input->findText(input) == -1){
        this->drop_down_input->addItem(input);
    }
}
