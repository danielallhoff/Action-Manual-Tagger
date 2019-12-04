#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <vector>
#include <QDir>
#include<QDebug>
#include <QtGui>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QSizePolicy>
#include <iostream>

#include "type.h"
class CustomWidget : public QWidget
{
    Q_OBJECT

    QGridLayout *gridLayout;
    QHBoxLayout *layout;
    QSlider *scroller;

    QLabel *action;
    QLabel *father;
    QLabel *idLabel;
    QLineEdit *input;
    QComboBox *drop_down_father;
    QComboBox *drop_down_input;
    Type type;
protected:
    QColor* getColor(Type type);

public:
    explicit CustomWidget(QWidget *parent = nullptr);
    CustomWidget();
    CustomWidget(QSet<QString> behaviours, Type type, int id, int initFrame);
    int getFrame();
    QString getInput();
    QString getFather();
    int getId();
    void setId(int id);
    void setInput(QString input);
    void addInput(QString input);
    Type getType(){return type;};
    void setWidget(int x, int y, QWidget* widget);
    virtual void setPrecision(int value);
signals:
    void somethingChanged(QWidget*);
public slots:
    void changed();
};

#endif // CUSTOMWIDGET_H
