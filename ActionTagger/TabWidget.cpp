#include "TabWidget.h"
#include "ImagesTab.h"
#include "VHDLTab.h"
#include "VideoTab.h"
//Create QTabwidget
TabWidget::TabWidget()
	: QWidget()
{
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);
	//mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}