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


class TabDialog : public QDialog
{
	Q_OBJECT

public:
	explicit TabDialog(QWidget *parent = nullptr);

private:
	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;
};

#endif