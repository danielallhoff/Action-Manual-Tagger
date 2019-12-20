#include "VideoTab.h"

//Create images widget
VideoTab::VideoTab(QWidget *parent)
	: TabWidget(parent)
{
	//https://doc.qt.io/archives/qt-4.8/phonon-videowidget.html
	player = new QMovie;
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget(player);
	main_layout->addStretch(1);
	setLayout(main_layout);
}

void VideoTab::init() {
	this->setFrame(0);
}

void VideoTab::last() {
	this->setFrame(player->frameCount()-1);
}
void VideoTab::pause() {
	player->setPaused(true);
}
void VideoTab::play() {
	player->start();
}
void VideoTab::setFrame(int frame) {
	player->jumpToFrame(frame);
}
void VideoTab::openFiles(QStringList url) {
	player->stop();
	player->setFileName(url[0]);
}
