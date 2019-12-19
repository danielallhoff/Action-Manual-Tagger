#include "VideoTab.h"

//Create images widget
VideoTab::VideoTab(QWidget *parent)
	: TabWidget()
{
	player = new QMediaPlayer;

}

void VideoTab::init() {
	player->setPosition(0);
}
void VideoTab::last() {
	player->setPosition(player->duration());
}
void VideoTab::pause() {
	player->pause();
}
void VideoTab::play() {
	player->play();
}
void VideoTab::setFrame(int frame) {

}
void VideoTab::openFiles(QStringList url) {
	player->setMedia(QUrl::fromLocalFile(url[0]));
}