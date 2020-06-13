#ifndef STATSTAB_H
#define STATSTAB_H

#include <QWidget>
#include "tasklist.h"

namespace Ui {
class statsTab;
}

class statsTab : public QWidget
{
    Q_OBJECT

public:
    explicit statsTab(QWidget *parent = nullptr);
    ~statsTab();

    //a string split function
    static std::vector<std::string> splitString(std::string string, char delimiter);


private:
    Ui::statsTab *ui;
    void individualPlot(std::string task);
    taskList *task;
};

#endif // STATSTAB_H
