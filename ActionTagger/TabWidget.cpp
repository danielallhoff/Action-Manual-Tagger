#include "TabWidget.h"
#include "ImagesTab.h"
#include "VHDLTab.h"
#include "VideoTab.h"
//Create QTabwidget
TabWidget::TabWidget()
	: QWidget()
{
	
	tabWidget = new QTabWidget();
	tabWidget->addTab(new VHDLTab(), tr("VHDL"));
	tabWidget->addTab(new ImagesTab(), tr("Images"));
	tabWidget->addTab(new VideoTab(), tr("Videos"));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);
	//mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}