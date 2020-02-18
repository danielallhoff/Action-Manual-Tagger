#ifndef MYQSLIDER_H
#define MYQSLIDER_H

#include <QWidget>
#include <QtGui>
#include <QtWidgets>
#include <QWidget>
#include <iostream>


class MyQSlider : public QSlider
{
	Q_OBJECT
public:	
	explicit MyQSlider(Qt::Orientation axis, QWidget *parent = nullptr) :QSlider(axis, parent) { };
	explicit MyQSlider() :QSlider() {};
	
	void installFilter() { this->installEventFilter(this); };
protected:
	void wheelEvent(QWheelEvent *event) { event->ignore(); };
	bool eventFilter(QObject *obj, QEvent *event);

	
};

#endif
