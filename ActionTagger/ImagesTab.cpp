#include "ImagesTab.h"

//Create images widget
ImagesTab::ImagesTab(QWidget *parent)
	: TabWidget(parent)
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
    if(frame == images.size()-1){
        frame = 0;
    }
    while (isPlaying && frame < images.size()) {
		QPixmap img(images[frame]);
		this->image_viewer->setPixmap(img);
		//34 milliseconds each frame
		Sleep(34);
        emit frameChanged(frame);
		++frame;
	}
}

//Play video with threading
void ImagesTab::play(){
    isPlaying = true;
	std::thread player_thread(&ImagesTab::playImages, this);
	player_thread.detach();
}

//Set Frame
void ImagesTab::setFrame(int frame) {
	QPixmap img(images[frame]);
	this->image_viewer->setPixmap(img);
	this->frame = frame;
    qDebug() << "Frame changed" << endl;
    emit frameChanged(frame);
}
void ImagesTab::openFiles(QStringList url) {
	this->images = url;
    setFrame(0);
	
}
