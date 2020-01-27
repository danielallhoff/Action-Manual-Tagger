
#ifndef VIDEOTAB_H
#define VIDEOTAB_H

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
#include <QMediaPlayer>
#include "TabWidget.h"

class VideoTab : public TabWidget
{
	Q_OBJECT

public:
	explicit VideoTab(QWidget *parent = nullptr);
	
	void init();
	void last();
	void pause();
	void play();
	void setFrame(int frame);
	void openFiles(QStringList url);
	int getTotalFrames() { return player->frameCount(); }
private slots:
    void frameChanging(int);
signals:
    void frameChanged(int);
private:
	QMovie *player;

};

#endif
