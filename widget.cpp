#include "widget.h"
#include "tasklist.h"
#include "optionstab.h"
#include "tasktab.h"
#include "statstab.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QDebug>

using namespace QtCharts;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //create the widgets
    taskList *task = new taskList(this);
    optionsTab *options = new optionsTab(this);
    taskTab *tasks = new taskTab(this);
    statsTab *stats = new statsTab(this);

    // create the main layout to include a list widget and a tabbed widget
    QHBoxLayout *mainLayout = new QHBoxLayout;

    // tabbed widget
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // add a new tab for the above widget
    tabs->addTab(tasks, "Task");

    // tab for stats widget
    tabs->addTab(stats, "Stats");

    // add buttonsLayout to tabbed widget (last tab)
    tabs->addTab(options, "Options");

    // create the main layout
    mainLayout->addWidget(task);
    mainLayout->addWidget(tabs);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}
