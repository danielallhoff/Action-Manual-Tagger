#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <set>

using json = nlohmann::json;

#include "interval.h"
#include "customwidget.h"
#include "customwidgetsubaction.h"
#include "TabWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void modifyFrameSlider();
    void add_behaviour();
    void modify_interval(QWidget* changed);
    void update_scroller(QSlider*);
    void add_action();
    void add_subaction();
    void create_json();
    void new_behaviour();
    void new_action();
    void new_subaction();
	void open_files();
	void tab_changed();
	void init();
	void last();
	void play();
	void pause();
    void frameChanged(int);
private:
	
	TabWidget *currentTab;

    Ui::MainWindow *ui;
	QStringList filenames;
    std::vector<Interval*> intervals;
    std::vector<QString> behaviours;
    std::vector<QString> actions;
    std::vector<QString> subactions;
    int firstFrame = 0;
    int lastFrame = 9;
    int totalFrames = 10;

    int behaviour_lastFrame = 0;
    int action_lastFrame = 0;
    int subaction_lastFrame = 0;
    int action_firstFrame = 0;

    int numBehaviours = 0;
    int numActions = 0;
    int numSubactions = 0;
    QString lastBehaviour = "";
    QString lastAction = "";

    int id = 0;
    Interval *last_behaviour = nullptr;
    Interval *last_action = nullptr;

    QSet<QString> behaviours_set;
    QSet<QString> actions_set;
    QSet<QString> subactions_set;
    QSet<QString> all_set;

    QString save_JSON = "saves";

    void add_itemWidget(Type type);
    void add_new(QString action_string, Type type);

    void save_to_JSON(QString name);
    void setFrameScroller(int frame);
};
#endif // MAINWINDOW_H
