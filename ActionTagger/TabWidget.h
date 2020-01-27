#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QMainWindow>
#include <vector>
#include <QDir>

#pragma comment(lib, "Ws2_32.lib")
#include <QDir>
#include<QDebug>
#include <QtGui>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QSizePolicy>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <qdialog.h>


#include "interval.h"
#include "customwidget.h"
#include "customwidgetsubaction.h"


class TabWidget : public QWidget
{
	Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    virtual void init() = 0;
    virtual void last() = 0;
    virtual void pause() = 0;
    virtual void play() = 0;
    virtual void setFrame(int frame) = 0;
    virtual void openFiles(QStringList url) = 0;
    virtual int getTotalFrames() = 0;

signals:
    void frameChanged(int);
};

#endif
