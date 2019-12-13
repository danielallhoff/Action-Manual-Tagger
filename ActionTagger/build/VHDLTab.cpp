#include "VHDLTab.h"

//Create vhdlTab
VHDLTab::VHDLTab(QWidget *parent)
	: QWidget(parent)
{
	QPushButton * play = new QPushButton();
	QPushButton * stop = new QPushButton();
	QPushButton * init = new QPushButton();
	QPushButton * last = new QPushButton();

	QVBoxLayout *controller_layout = new QVBoxLayout();
	
	controller_layout->addWidget(init);
	controller_layout->addWidget(play);
	controller_layout->addWidget(stop);
	controller_layout->addWidget(last);
	controller_layout->addStretch(1);
	setLayout(controller_layout);
}