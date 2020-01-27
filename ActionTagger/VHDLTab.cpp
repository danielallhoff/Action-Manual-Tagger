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
	setFrame(getTotalFrames());
}
void VHDLTab::pause() {
	std::thread client_thread(&BHVClient::sendMessage, "stop");
	client_thread.detach();
}
void VHDLTab::play() {
	std::thread client_thread(&BHVClient::sendMessage, "play");
	client_thread.detach();
}

int VHDLTab::getTotalFrames() {
	if (totalFrames == -1) {
		std::thread client_thread(&BHVClient::sendMessage, "get");
		client_thread.join();
		totalFrames = std::stoi(BHVClient::getResult());
		return totalFrames;
	}
	else {
		return totalFrames;
	}
}

void VHDLTab::setFrame(int frame) {
	std::thread client_thread(&BHVClient::sendMessage, "set " + std::to_string(frame));
	client_thread.detach();
    emit frameChanged(frame);
}
