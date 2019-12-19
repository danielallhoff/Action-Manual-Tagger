#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QMainWindow>
#include <vector>
#include <QDir>

#pragma comment(lib, "Ws2_32.lib")
#include <QDir>
#include<QDebug>
#include <QtGui>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QSizePolicy>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <qdialog.h>


#include "interval.h"
#include "customwidget.h"
#include "customwidgetsubaction.h"


class TabWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TabWidget();
	void init();
	void last();
	void pause();
	void play();
	void setFrame(int frame);
	void openFiles(QStringList url);
private:
	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;
};

#endif