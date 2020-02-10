
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
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp> 

using namespace cv;
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
	int getTotalFrames() { return totalFrames; }
private slots:
    void frameChanging(int);
signals:
    void frameChanged(int);
private:
//	QMovie *player;
	QLabel *image_viewer;
	VideoCapture cap;
	int totalFrames = -1;
	int frame = -1;
	bool isPlaying = false;
	void playImages();
	std::vector<QPixmap> images;
	inline QImage cvMatToQIMage(const cv::Mat &inMat);
	inline QPixmap cvMatToQPixmap(const cv::Mat &inMat)
	{
		return QPixmap::fromImage(cvMatToQIMage(inMat));
	}
};

#endif
