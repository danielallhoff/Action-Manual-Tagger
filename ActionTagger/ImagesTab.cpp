#include "ImagesTab.h"

//Create images widget
ImagesTab::ImagesTab(QWidget *parent)
	: QWidget(parent)
{
	QLabel* image_viewer = new QLabel();
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget(image_viewer);
	main_layout->addStretch(1);
	setLayout(main_layout);
}