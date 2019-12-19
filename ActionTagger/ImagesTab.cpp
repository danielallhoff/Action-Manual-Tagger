#include "ImagesTab.h"

//Create images widget
ImagesTab::ImagesTab(QWidget *parent)
	: QWidget(parent)
{
	image_viewer = new QLabel();
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget(image_viewer);
	main_layout->addStretch(1);
	setLayout(main_layout);
}

//Set image as start
void ImagesTab::init() {
	setFrame(0);
}

//Set last image
void ImagesTab::last() {
	setFrame(images.size() - 1);
}

//Pause video if playing
void ImagesTab::pause() {
	isPlaying = false;
}
//Play images with 30 fps
void ImagesTab::playImages() {
	while (isPlaying) {
		QPixmap img(images[frame]);
		this->image_viewer->setPixmap(img);
		//34 milliseconds each frame
		Sleep(34);
		++frame;
	}
}

//Play video with threading
void ImagesTab::play(){
	std::thread player_thread(this->playImages);
	player_thread.detach();
}

//Set Frame
void ImagesTab::setFrame(int frame) {
	QPixmap img(images[frame]);
	this->image_viewer->setPixmap(img);
	this->frame = frame;
}
void ImagesTab::openFiles(QStringList url) {
	this->images = url;
}