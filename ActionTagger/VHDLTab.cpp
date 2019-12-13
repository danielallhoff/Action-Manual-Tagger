#include "VHDLTab.h"

//Create vhdlTab
VHDLTab::VHDLTab(QWidget *parent, QMainWindow* main)
	: QWidget(parent)
{
	QPushButton * play = new QPushButton();
	QPushButton * stop = new QPushButton();
	QPushButton * init = new QPushButton();
	QPushButton * last = new QPushButton();
	/*	
	QPushButton *button = new QPushButton;
	button->setIcon(QIcon(":/icons/..."));
	button->setIconSize(QSize(65, 65));
	*/
	QVBoxLayout *controller_layout = new QVBoxLayout();
	
	controller_layout->addWidget(init);
	controller_layout->addWidget(play);
	controller_layout->addWidget(stop);
	controller_layout->addWidget(last);
	controller_layout->addStretch(1);
	setLayout(controller_layout);

	//Connect each button to mainwindow function
	connect(init, SIGNAL(clicked()), main, SLOT(init_clicked()));
	connect(play, SIGNAL(clicked()), main, SLOT(play_clicked()));
	connect(stop, SIGNAL(clicked()), main, SLOT(stop_clicked()));
	connect(last, SIGNAL(clicked()), main, SLOT(last_clicked()));

}