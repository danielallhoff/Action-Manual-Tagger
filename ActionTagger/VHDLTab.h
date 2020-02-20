#ifndef VHDLTAB_H
#define VHDLTAB_H

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
#include "TabWidget.h"

class VHDLTab : public TabWidget
{
	Q_OBJECT

public:
    explicit VHDLTab(QWidget *parent = nullptr);
	void checkTotalFrames();
	void init();
	void last();
	void pause();
	void play();
	void setFrame(int frame);
    int getTotalFrames();
    void openFiles(QStringList url){}

signals:
    void frameChanged(int);
	void updateTotalFrames(int);
private:
	int totalFrames = -1;


	
};

#endif
