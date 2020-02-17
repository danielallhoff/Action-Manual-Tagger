#ifndef QSLIDER_H
#define QSLIDER_H

#include <QMainWindow>
#include <vector>
#include <QDir>

#include <QDir>
#include<QDebug>
#include <QtGui>

#include <QWidget>

#include <iostream>
#include <QSlider>
#include <fstream>
#include <iomanip>
#include <set>
#include <qdialog.h>

#include <QSlider>

class MyQSlider : public QSlider
{
	Q_OBJECT

public:
	MyQSlider(QWidget *parent = nullptr);
	void wheelEvent(QWheelEvent *event) override { event.ignore(); }
signals:
	void frameChanged(int);
};

#endif
