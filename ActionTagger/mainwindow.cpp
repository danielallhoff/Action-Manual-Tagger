#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ImagesTab.h"
#include "VHDLTab.h"
#include "VideoTab.h"
#include "TabWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    firstFrame= 0;
    lastFrame = 9;
    totalFrames = 10;
    action_firstFrame = 0;
    action_lastFrame = 10;
    behaviour_lastFrame = 0;

    lastBehaviour = "";
    lastAction = "";
    int lastFrame = -1;

    id = 0;
    //Clear default tabs
    ui->tabWidget->clear();
    bool resourcesLoaded = false;
    //Add new tabs
    TabWidget* VHDLTabWidget = new VHDLTab();
    ImagesTab* ImagesTabWidget = new ImagesTab();
    VideoTab* VideoTabWidget = new VideoTab();
    connect(VHDLTabWidget, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
    connect(ImagesTabWidget, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
    connect(VideoTabWidget, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
    ui->tabWidget->addTab(VHDLTabWidget, tr("VHDL"));
    ui->tabWidget->addTab(ImagesTabWidget, tr("Images"));
    ui->tabWidget->addTab( VideoTabWidget, tr("Videos"));

	//File opener
	connect(ui->open, SIGNAL(clicked()), this, SLOT(open_files()));

	//Buttons
	connect(ui->init, SIGNAL(clicked()), this, SLOT(init()));
	connect(ui->play, SIGNAL(clicked()), this, SLOT(play()));
	connect(ui->pause, SIGNAL(clicked()), this, SLOT(pause()));
	connect(ui->last, SIGNAL(clicked()), this, SLOT(last()));
	
    //Frames scroller
    connect(ui->frameSlider,SIGNAL(valueChanged(int)),this,SLOT(modifyFrameSlider()));
    //connect(ui->action_initFrame,SIGNAL(returnPressed()),this,SLOT(modifyFrame_slider()));
	
    //Add a new widget of type behaviour/action or subaction
    connect(ui->add_behaviour,SIGNAL(clicked()), this, SLOT(add_behaviour()));
    connect(ui->add_action,SIGNAL(clicked()), this, SLOT(add_action()));
    connect(ui->add_subaction,SIGNAL(clicked()), this, SLOT(add_subaction()));

    //Add a new behaviour/action or subaction
    connect(ui->new_behaviour,SIGNAL(clicked()), this, SLOT(new_behaviour()));
    connect(ui->new_action,SIGNAL(clicked()), this, SLOT(new_action()));
    connect(ui->new_subaction,SIGNAL(clicked()), this, SLOT(new_subaction()));

	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tab_changed()));
    //End tagging
    connect(ui->finish_tagging,SIGNAL(clicked()), this, SLOT(create_json()));

    qDebug() << "Started" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Tab widget index changed.*/
void MainWindow::tab_changed() {
    currentTab = dynamic_cast<TabWidget*>(ui->tabWidget->currentWidget());
    qDebug() << "Tab changed" << endl;
}

void MainWindow::frameChanged(int frame){

    if(frame < 0){
        frame = 0;
    }else if(frame >= totalFrames){
        frame = totalFrames - 1;
    }

    ui->frameSlider->setValue(frame);

}

void MainWindow::init() {
    try {
        currentTab->init();
    } catch (QException exception) {
        QMessageBox::warning(this, tr("Manual Tagger"),
            tr("Resources yet not loaded. Open a resource."),
            QMessageBox::Cancel);
    }

}
void MainWindow::last() {
    try {
        currentTab->last();
    } catch (QException exception) {
        QMessageBox::warning(this, tr("Manual Tagger"),
            tr("Resources yet not loaded. Open a resource."),
            QMessageBox::Cancel);
    }

}
void MainWindow::play(){
    try {
        currentTab->play();
    } catch (QException exception) {
        QMessageBox::warning(this, tr("Manual Tagger"),
            tr("Resources yet not loaded. Open a resource."),
            QMessageBox::Cancel);
    }

}
void MainWindow::pause() {
    try {
        currentTab->pause();
    } catch (QException exception) {
        QMessageBox::warning(this, tr("Manual Tagger"),
            tr("Resources yet not loaded. Open a resource."),
            QMessageBox::Cancel);
    }

}

void MainWindow::open_files() {
	//VHDL TAB
	if (ui->tabWidget->currentIndex() == 0) {
		QMessageBox::warning(this, tr("Manual Tagger"),
			tr("Cannot open vhdl files, open external interface bvhsource!"),
			QMessageBox::Cancel);
	}

	//Images TAB
	if (ui->tabWidget->currentIndex() == 1) {
		QString fileNames_filters = "Images (*.png *.xpm *.jpg *.jpeg";
		QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select multiple images"), QDir::homePath(), fileNames_filters);
		if (!fileNames.isEmpty()) {
			this->filenames = fileNames;
			currentTab->openFiles(filenames);
			totalFrames = currentTab->getTotalFrames();
			lastFrame = totalFrames - 1;            
		}
	}

	//Video TAB
	if (ui->tabWidget->currentIndex() == 2) {
        QString fileNames_filters = "Videos (*.avi *.mp4 *.mov *.mpg *.gif)";
		QString fileNames = QFileDialog::getOpenFileName(this, tr("Select a video"), QDir::homePath(), fileNames_filters);
		if (!fileNames.isEmpty()) {
			this->filenames.clear();
			this->filenames.append(fileNames);
			currentTab->openFiles(filenames);
			totalFrames = currentTab->getTotalFrames();
			lastFrame = totalFrames - 1;            
		}
	}

	
}

/** When a qtlistwidgetitem is modified(slider, label, father...etc) it updates the interval.
 * @brief MainWindow::modify_interval
 */
void MainWindow::modify_interval(QWidget* changed){

    CustomWidget* widget = (CustomWidget*) changed;
    int id = widget->getId();
    behaviour_lastFrame = widget->getFrame();
    intervals[id]->setName(widget->getInput());
    if(widget->getType() != SUBACTION){
        intervals[id]->setLastFrame(widget->getFrame());
    }else{
        intervals[id]->setInitFrame(widget->getFrame());
        CustomWidgetSubaction* widget_subaction = (CustomWidgetSubaction*) widget;
        intervals[id]->setLastFrame(widget_subaction->getLastFrame());
    }
}
/**When modify clicked update scroller
 * @brief MainWindow::update_scroller
 */
void MainWindow::update_scroller(QSlider* slider){
    int value = ui->frameSlider->value();
    slider->setValue(value);
}

void MainWindow::create_json(){
    QString filename = ui->filename_input->text();

    save_to_JSON(filename);
}

/** Modifies the value by slider
 * @brief MainWindow::modifyFrameSlider
 */
void MainWindow::modifyFrameSlider(){

    int frameValue = ui->frameSlider->value();
	
    //Convert to frame number
	frameValue = (totalFrames * frameValue)/totalFrames*1.0;
	currentTab->setFrame(frameValue);
	/*lastFrame = 
	totalFrames = lastFrame + 1;
	std::cout << lastFrame << endl;*/
	if (lastFrame > 0) {
		ui->frameSlider->setMaximum(totalFrames - 1);
	}
	
	
    action_firstFrame = frameValue;

}


/** Slider for going through images
 * @brief MainWindow::modifyInitFrame_slider
 
void MainWindow::modifyFrame_slider(){
	QString valueInitFrame = ui->action_initFrame->text();
    bool ok;
    int valueInt= valueInitFrame.toInt(&ok);
    if(ok){
        if(valueInt < 0){
            valueInt = 0;
        }else if(valueInt >= totalFrames){
            valueInt = totalFrames - 1;
        }
        valueInt = (totalFrames * valueInt)/totalFrames*1.0;
        action_firstFrame = valueInt;
        ui->frameSlider->setValue(valueInt);
    }
}*/

/** Add a behaviour widget
 * @brief MainWindow::add_action
 */
void MainWindow::add_behaviour(){
   add_itemWidget(BEHAVIOUR);
}
/** Add a new action widget
 * @brief MainWindow::add_action
 */
void MainWindow::add_action(){
   add_itemWidget(ACTION);
}

/** Add a new subaction widget
 * @brief MainWindow::add_subaction
 */
void MainWindow::add_subaction(){
    add_itemWidget(SUBACTION);
}

/** New behaviour
 * @brief MainWindow::new_behaviour
 */
void MainWindow::new_behaviour(){
    QString action_string = ui->new_value->text();

    if(action_string != "" && !all_set.contains(action_string)){
        behaviours.push_back(action_string);
        lastBehaviour = action_string;
        add_new(action_string, BEHAVIOUR);
    }else{
        QMessageBox::warning(
            this,
            tr("Manual Tagger"),
            tr("Empty or already exists! Hint: do not repeat names") );
    }
}
/** New action
 * @brief MainWindow::new_action
 */
void MainWindow::new_action(){
    QString action_string = ui->new_value->text();

    if(action_string != "" && !all_set.contains(action_string)){
        actions.push_back(action_string);
        lastAction = action_string;
        add_new(action_string, ACTION);
    }else{
        QMessageBox::warning(
            this,
            tr("Manual Tagger"),
            tr("Empty or already exists! Hint: do not repeat names") );
    }
}

/** New subaction
 * @brief MainWindow::new_subaction
 */
void MainWindow::new_subaction(){
    QString action_string = ui->new_value->text();

    if(action_string != "" && !all_set.contains(action_string)){
        subactions.push_back(action_string);
        add_new(action_string, SUBACTION);
    }else{
        QMessageBox::warning(
            this,
            tr("Manual Tagger"),
            tr("Empty or already exists! Hint: do not repeat names") );
    }
}

/** Add new value of behaviour/action or subaction
 * @brief MainWindow::add_new
 * @param action_string
 * @param type
 */
void MainWindow::add_new(QString action_string, Type type){
    all_set.insert(action_string);

    switch(type){
        case BEHAVIOUR:
            if(!behaviours_set.contains(action_string)){
                ui->behaviours_list->addItem(action_string);
                behaviours_set.insert(action_string);
            }
            break;
        case ACTION:
            if(!actions_set.contains(action_string)){
                ui->actions_list->addItem(action_string);
                actions_set.insert(action_string);
            }
            break;
        case SUBACTION:
            if(!subactions_set.contains(action_string)){
                ui->subactions_list->addItem(action_string);
                subactions_set.insert(action_string);
            }
            break;

    }

    for(int i = 0; i < ui->listIntervals->count(); ++i){
        QListWidgetItem* item = ui->listIntervals->item(i);
        QWidget* widget = ui->listIntervals->itemWidget(item);
        CustomWidget *custom = (CustomWidget*) widget;
        custom->addInput(action_string);
    }

}
/** Adds a brehaviour/action/subaction widget to the listwidget
 * @brief MainWindow::add_itemWidget
 * @param action_string
 * @param type
 */
void MainWindow::add_itemWidget(Type type){
    QListWidgetItem *newItem = new QListWidgetItem();

    CustomWidget *widget;
    Interval *newInterval;

    bool new_item = false;
    int pos = 0;

    switch(type){
        case BEHAVIOUR:
            pos = numBehaviours;
            ++numBehaviours;

            newInterval = new Interval("null", 0, behaviour_lastFrame, type, last_behaviour);
            last_behaviour = newInterval;
            widget = new CustomWidget(all_set, type, id,behaviour_lastFrame);

            break;
        case ACTION:
            pos = numBehaviours+numActions;
            ++numActions;

            newInterval = new Interval("null", 0, action_lastFrame, type, last_action);
            last_action = newInterval;
            widget = new CustomWidget(all_set, type, id,action_lastFrame);
            break;
        case SUBACTION:
            pos = numBehaviours+numActions+numSubactions;
            ++numSubactions;

            newInterval = new Interval("null", 0, subaction_lastFrame, type, nullptr);
            widget = new CustomWidgetSubaction(all_set, type, id,subaction_lastFrame);

            break;

    }
    widget->setPrecision(totalFrames-1);


    connect(widget,SIGNAL(somethingChanged(QWidget*)), this, SLOT(modify_interval(QWidget*)));
    connect(widget,SIGNAL(adjustScroller(QSlider*)), this, SLOT(update_scroller(QSlider*)));
    ui->listIntervals->insertItem(pos, newItem);
    ui->listIntervals->setItemWidget(newItem,widget);

    intervals.push_back(newInterval);
    ++id;
}

/** Saves behaviour segmentation in a readable JSON format
 * @brief MainWindow::save_to_JSON
 * @param name
 */
void MainWindow::save_to_JSON(QString name){
    if(!intervals.empty()){
        json j;

        std::set<std::string> behaviours;
        std::set<std::string> actions;
        std::set<std::string> subactions;
        std::set<std::string> all;
        std::vector<Interval*> behavioursIntervals;
        std::vector<Interval*> actionsIntervals;
        std::vector<Interval*> subactionsIntervals;
        //Extract all intervals
        for(int i = 0; i < intervals.size(); ++i){
            Type type = intervals[i]->getType();
            std::string name = intervals[i]->getName().toStdString();

            if(type == BEHAVIOUR){
                behaviours.insert(name);
                behavioursIntervals.push_back(intervals[i]);
            }else if(type == ACTION){
                actions.insert(name);
                actionsIntervals.push_back(intervals[i]);
            }else if(type == SUBACTION){
                subactions.insert(name);
                subactionsIntervals.push_back(intervals[i]);
            }
        }

        //Use as id for each behaviour in json file
        std::map<std::string, int> getId;

        int id = 0;

        for(std::string s: behaviours){
            all.insert(s);
        }
        for(std::string s: actions){
            all.insert(s);
        }

        for(std::string s: subactions){
            all.insert(s);
        }

        for(std::string s: all){
            getId[s] = id;
            ++id;
        }

        //Set behaviours frames
        std::vector<int> behavioursFrames(totalFrames, -1);
        for(int i = 0; i < behavioursIntervals.size(); i++){
            Interval* behaviour = behavioursIntervals[i];
            int initFrame = 0;
            int lastFrame = 0;
            if(i != 0){
                initFrame = behaviour->getFather()->getLastFrame();
            }
            for(int j= initFrame; j <= behaviour->getLastFrame(); j++){
                behavioursFrames[j] = getId[behaviour->getName().toStdString()];
            }
        }
        //Set actions frames
        std::vector<int> actionsFrames(totalFrames, -1);
        for(int i = 0; i < actionsIntervals.size(); i++){
            Interval* action = actionsIntervals[i];
            int initFrame = 0;
            if(i != 0){
                initFrame = action->getFather()->getLastFrame();
            }
            for(int j= initFrame; j <= action->getLastFrame(); j++){
                actionsFrames[j] = getId[action->getName().toStdString()];
            }
        }

        //Set subactions frames
        std::vector<std::vector<int>> subactionsFrames(totalFrames, std::vector<int>(1,-1));
        for(int i = 0; i < subactionsIntervals.size(); i++){
            Interval* subaction = subactionsIntervals[i];
            for(int j= subaction->getInitFrame(); j <= subaction->getLastFrame(); j++){
                if(subactionsFrames[j][0] != -1){
                    subactionsFrames[j].push_back(getId[subaction->getName().toStdString()]);
                }else{
                    subactionsFrames[j][0] = getId[subaction->getName().toStdString()];
                }

            }
        }
        //Assign to json
        j["name"] = name.toStdString();
        j["frames"] = totalFrames;
        j["behaviours"] = behaviours;
        j["actions"] = actions;
        j["subactions"] = subactions;

        j["sequence"]["behaviours"] = behavioursFrames;
        j["sequence"]["actions"] = actionsFrames;
        j["sequence"]["subactions"] = subactionsFrames;
        //Output to file
        std::ofstream o(name.toStdString()+".json");
        //Output mode
        o << std::setw(4) << j << std::endl;
        //o << j << std::endl;
        QMessageBox::information(
            this,
            tr("Manual Tagger"),
            tr("JSON file is well created!") );
    }
}


