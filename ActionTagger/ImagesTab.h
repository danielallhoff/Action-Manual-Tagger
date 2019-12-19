#ifndef IMAGESTAB_H
#define IMAGESTAB_H

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


class ImagesTab : public QWidget
{
	Q_OBJECT

public:
	explicit ImagesTab(QWidget *parent = nullptr);
	void init();
	void last();
	void pause();
	void play();
	void setFrame(int frame);
	void openFiles(QStringList url);
private:
	QStringList images;
	QLabel* image_viewer;
	void playImages();
	bool isPlaying = false;
	int frame;
};

#endif