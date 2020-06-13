#ifndef TASKLIST_H
#define TASKLIST_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class taskList;
}
extern QListWidget *subjectsList;
extern std::vector<std::string> subjects; // a vector to keep track of all tasks
class taskList : public QWidget
{
    Q_OBJECT

public:
    explicit taskList(QWidget *parent = nullptr);
    ~taskList();

    static std::vector<std::string> splitString(std::string string, char delimiter);


private:
    Ui::taskList *ui;
};
#endif // TASKLIST_H

