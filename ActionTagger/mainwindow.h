#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QDir>


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
    void modifyFrame_text();
    void modifyFrame_slider();
    void add_behaviour();
    void modify_interval(QWidget* changed);
    void update_scroller(QSlider*);
    void add_action();
    void add_subaction();
    void create_json();
    void new_behaviour();
    void new_action();
    void new_subaction();
private:
    Ui::MainWindow *ui;

    std::vector<Interval*> intervals;
    std::vector<QString> behaviours;
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

    QStringList frames;
    QString directory = "frames";
    QString save_JSON = "saves";

    void load_images();
    void load_image_to_screen(QString filename);

    void add_itemWidget(Type type);
    void add_new(QString action_string, Type type);

    void save_to_JSON(QString name);
};
#endif // MAINWINDOW_H
