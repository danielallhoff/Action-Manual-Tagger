#include "VHDLTab.h"
#include "BHVClient.h"
//Create vhdlTab
VHDLTab::VHDLTab(QWidget *parent)
	: TabWidget(parent)
{
	
	totalFrames = -1;
}

void VHDLTab::init() {
	setFrame(0);
}
void VHDLTab::last() {
	setFrame(totalFrames-1);
}
void VHDLTab::pause() {
	std::thread client_thread(&BHVClient::sendMessage, "stop");
	client_thread.detach();
}
void VHDLTab::play() {
	std::thread client_thread(&BHVClient::sendMessage, "play");
	client_thread.detach();
}

void VHDLTab::checkTotalFrames() {
	if (totalFrames == -1) {
		totalFrames = this->getTotalFrames();
		emit updateTotalFrames(totalFrames);
	}
	
}

int VHDLTab::getTotalFrames() {
	if (totalFrames == -1) {
		std::thread client_thread(&BHVClient::sendMessage, "get MAX_VALUE");
		client_thread.join();
		totalFrames = std::stoi(BHVClient::getResult());
		return totalFrames;
	}
	else {
		return totalFrames;
	}
}

void VHDLTab::setFrame(int frame) {
	checkTotalFrames();
	std::thread client_thread(&BHVClient::sendMessage, "set " + std::to_string(frame));
	client_thread.detach();
    emit frameChanged(frame);
}
