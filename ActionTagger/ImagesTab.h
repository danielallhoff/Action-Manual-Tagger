#ifndef IMAGESTAB_H
#define IMAGESTAB_H

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


class ImagesTab : public QWidget
{
	Q_OBJECT

public:
	explicit ImagesTab(QWidget *parent = nullptr);

private:
	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;
};

#endif