#include "tasklist.h"
#include "ui_tasklist.h"
#include <QListWidget>
#include <fstream>
#include <QDebug>
#include <vector>
#include <QVBoxLayout>

QListWidget *subjectsList;
std::vector<std::string> subjects;
taskList::taskList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskList)
{
    ui->setupUi(this);
    // list widget
    subjectsList = new QListWidget(this);
    // check for a already existing file and load task names data
    std::fstream file;
    file.open("data.txt", std::ios::in);
    if(file.is_open()) {
        qDebug() << "file has been found. object memory address: " << subjectsList;
        std::string line;

        while(std::getline(file, line)) {
            std::vector<std::string> strings = splitString(line, ',');
            if(std::find(subjects.begin(), subjects.end(), strings[3]) != subjects.end()) {
                continue;
            }
            else {
                subjects.push_back(strings[3]);
                subjectsList->addItem(QString::fromStdString(strings[3]));
            }
        }
    }
    else {
        qDebug() << "no file has been found";
    }

    //create a layout for the widget
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(subjectsList);
}

taskList::~taskList()
{
    delete ui;
}

std::vector<std::string> taskList::splitString(std::string string, char delimiter) {
    std::vector<std::string> results;
    std::string currentString;
    for(auto c:string) {
        if(c == delimiter) {
            results.push_back(currentString);
            currentString = "";
        }
        else {
            currentString += c;
        }
    }
    results.push_back(currentString); //add the last string after the last delimiter char
    return results;
}
