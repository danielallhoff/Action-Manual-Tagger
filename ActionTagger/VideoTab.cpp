#include "VideoTab.h"

//Create images widget
VideoTab::VideoTab(QWidget *parent)
	: TabWidget(parent)
{
	QVBoxLayout *main_layout = new QVBoxLayout;
    image_viewer = new QLabel(tr("No video loaded"));	    
	main_layout->addWidget(image_viewer);
	main_layout->addStretch(1);
	setLayout(main_layout);
    
    //connect(this, SIGNAL(frameChanged(int)), this, SLOT(frameChanging(int)));

};

void VideoTab::frameChanging(int frame){
    emit frameChanged(frame);
}

void VideoTab::init() {
	this->setFrame(0);
}

void VideoTab::last() {
	this->setFrame(totalFrames-1);
}

//Play images with 30 fps
void VideoTab::playImages() {
	if (isPlaying && frame == totalFrames -1) {
		frame = 0;
	}
	while (isPlaying && frame < totalFrames) {
		this->image_viewer->setPixmap(images[frame]);
		//34 milliseconds each frame
		Sleep(34);
		emit frameChanged(frame);
		++frame;
	}
}

void VideoTab::pause() {
	isPlaying = false;
}
void VideoTab::play() {
	isPlaying = true;
	std::thread player_thread(&VideoTab::playImages, this);
	player_thread.detach();
}
void VideoTab::setFrame(int frame) {
	if (frame >= 0 && frame <= totalFrames) {
		qDebug() << "Frame changed" << endl;
		emit frameChanged(frame);
		this->frame = frame;
		this->image_viewer->setPixmap(images[frame]);		
	}
}
void VideoTab::openFiles(QStringList url) {
	cv::VideoCapture cap = cv::VideoCapture(url[0].toStdString());
	totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
	images.resize(totalFrames);
	frame = 0;
	image_viewer->setText("Loading...");
	for (;;) {
		cv::Mat cvframe;
		cap >> cvframe;
		if (cvframe.empty())
			break;
		cv::Mat cvframe_resized;
		cv::resize(cvframe, cvframe_resized, cv::Size(IMG_WIDTH, IMG_HEIGHT), cv::INTER_AREA);
		QPixmap img = cvMatToQPixmap(cvframe_resized);
		images[frame] = img;
		++frame;
	}
	setFrame(0);
}

QImage VideoTab::cvMatToQIMage(const cv::Mat &inMat) {
	/*switch (inMat.type())
	{
		// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_ARGB32);

		return image;
	}

	// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_RGB888);

		return image.rgbSwapped();
	}

	// 8-bit, 1 channel
	case CV_8UC1:
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_Grayscale8);
#else
		static QVector<QRgb>  sColorTable;

		// only create our color table the first time
		if (sColorTable.isEmpty())
		{
			sColorTable.resize(256);

			for (int i = 0; i < 256; ++i)
			{
				sColorTable[i] = qRgb(i, i, i);
			}
		}

		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_Indexed8);

		image.setColorTable(sColorTable);
#endif

		return image;
	}

	default:
		qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
		break;
	}
	*/
	QImage imgIn = QImage((uchar*)inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);
	return imgIn;
}
