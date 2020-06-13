#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include <QWidget>

namespace Ui {
class optionsTab;
}

class optionsTab : public QWidget
{
    Q_OBJECT

public:
    explicit optionsTab(QWidget *parent = nullptr);
    ~optionsTab();

private:
    Ui::optionsTab *ui;
};

#endif // OPTIONSTAB_H
