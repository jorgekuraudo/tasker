#include "tasktab.h"
#include "tasklist.h"
#include "widget.h"
#include "ui_tasktab.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <fstream>
#include <QThread>

taskTab::taskTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskTab)
{

    ui->setupUi(this);
    // a layout with two buttons to start/stop task
    QWidget *startStopWidget = new QWidget(this);
    QVBoxLayout *startStopLayout = new QVBoxLayout;
    //start button
    QPushButton *startTask = new QPushButton("  Start");
    startTask->setIcon(QIcon(":/new/prefix1/start.png"));
    startTask->setIconSize(QSize(32,32));
    startTask->setToolTip("Start reconding a new task");
    //stop button
    QPushButton *stopTask = new QPushButton("  Stop");
    stopTask->setIcon(QIcon(":/new/prefix1/stop.png"));
    stopTask->setIconSize(QSize(32,32));
    stopTask->setToolTip("Stop currently running task");
    //show info button
    QPushButton *showTime = new QPushButton("  Show time");
    showTime->setIcon(QIcon(":/new/prefix1/show.png"));
    showTime->setIconSize(QSize(32,32));
    showTime->setToolTip("Show aditional info");
    //display current time
    QLabel *display = new QLabel();
    display->setAlignment(Qt::AlignRight);

    startStopLayout->setSpacing(10);
    startStopLayout->addWidget(startTask);
    startStopLayout->addWidget(stopTask);
    startStopLayout->addWidget(showTime);
    startStopLayout->addWidget(display);
    startStopLayout->addStretch(1);

    startStopWidget->setLayout(startStopLayout);


    // start a task
    connect(startTask, &QPushButton::clicked, [=](){
        qDebug() << "before accesing the task class";
        //QString taskName = task->subjectsList->currentItem()->text();
        //qDebug() << taskName << " has started. Current date:\n";
        std::string *currentDate = tdate();
        qDebug() << QString::fromStdString(currentDate[0]);
        qDebug() << QString::fromStdString(currentDate[1]);
        qDebug() << QString::fromStdString(currentDate[2]);
        delete  []currentDate;
        if(isTaskActive) {
            qDebug() << "task already started";
        }
        else {
            isTaskActive = true;
            taskTime.start();
        }

    });

    // stop a task
    connect(stopTask, &QPushButton::clicked, [=](){
        if(isTaskActive) {
            isTaskActive = false;
            elapsedTime = taskTime.elapsed();
            qDebug() << "time elapsed: " << elapsedTime;
            // write the data
            this->dataToFile();
        }
        else {
            qDebug() << "start a task first";
        }

    });

    // show elapsed time
    connect(showTime, &QPushButton::clicked, [=](){

        if(isTaskActive) {
            qDebug() << taskTime.elapsed();
            int *formatedTime;
            formatedTime = this->formatTime(taskTime.elapsed());
            qDebug() << "hours: " << formatedTime[0];
            qDebug() << "minutes: " << formatedTime[1];
            qDebug() << "seconds: " << formatedTime[2];
            display->setWordWrap(true);
            display->setText("Hours: "+ QString::number(formatedTime[0])
                    +"\nMinutes: "+QString::number(formatedTime[1])
                    +"\nSeconds: "+QString::number(formatedTime[2]));
            delete []formatedTime;
        }
    });
}

taskTab::~taskTab()
{
    delete ui;
}


std::string *taskTab::tdate() {
    time_t actual_time = time(0);
    tm *local_time = localtime(&actual_time);

    std::string *currentDate = new std::string[3];
    currentDate[0] = std::to_string(local_time->tm_year + 1900);
    currentDate[1] = std::to_string(local_time->tm_mon + 1);
    currentDate[2] = std::to_string(local_time->tm_mday);

    return currentDate;
}

void taskTab::dataToFile() {
    std::fstream file;
    file.open("data.txt", std::ios::in | std::ios::out | std::ios::app);

    std::string *currentDate = tdate();

    file << currentDate[0] << ',' << currentDate[1] << ',' << currentDate[2] << ',' <<
                             subjectsList->currentItem()->text().toStdString() << ',' << elapsedTime << '\n';
    delete[] currentDate;
}


int* taskTab::formatTime(int milliseconds) {
    int hours;
    int minutes;
    int seconds;

    if(milliseconds / (1000*60*60)) {
        hours = milliseconds / (1000*60*60);
        milliseconds -= hours * 1000*60*60;
    } else {
        hours = 0;
    }

    if(milliseconds / (1000*60)) {
        minutes = milliseconds / (1000*60);
        milliseconds -= minutes * 1000*60;
    } else {
        minutes = 0;
    }

    if(milliseconds / (1000)) {
        seconds = milliseconds / (1000);
    } else {
        seconds = 0;
    }

    int *results = new int[3];
    results[0] = hours;
    results[1] = minutes;
    results[2] = seconds;
    return results;
}
