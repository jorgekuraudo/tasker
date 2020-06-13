#ifndef TASKTAB_H
#define TASKTAB_H

#include <QWidget>
#include <QTime>
#include "tasklist.h"

namespace Ui {
class taskTab;
}

class taskTab : public QWidget
{
    Q_OBJECT

public:
    explicit taskTab(QWidget *parent = nullptr);
    ~taskTab();

    static std::string *tdate();

    static int* formatTime(int milliseconds);

    bool isTaskActive = false;


private:
    Ui::taskTab *ui;

    taskList *task;
    QTime taskTime;
    int elapsedTime;
    void dataToFile();
};

#endif // TASKTAB_H
