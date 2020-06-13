#include "optionstab.h"
#include "widget.h"
#include "tasklist.h"
#include "ui_optionstab.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QDebug>

optionsTab::optionsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optionsTab)
{
    ui->setupUi(this);
    // a layout containing two buttons for the first tab
    QWidget *optionsWidget = new QWidget(this);
    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    //add button
    QPushButton *add = new QPushButton("  Add");
    add->setIcon(QIcon(":/new/prefix1/add.png"));
    add->setIconSize(QSize(32,32));
    add->setToolTip("Add a new task to your list");
    add->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    //remove button
    QPushButton *remove = new QPushButton("  Remove");
    remove->setIcon(QIcon(":/new/prefix1/remove.png"));
    remove->setIconSize(QSize(32,32));
    remove->setToolTip("Remove a task");

    //buttonsLayout->setSpacing(10);
    buttonsLayout->addWidget(add);
    buttonsLayout->addWidget(remove);
    //buttonsLayout->addStretch(1);

    optionsWidget->setLayout(buttonsLayout);


    // set buttons connections
    // add a task
    connect(add, &QPushButton::clicked, [=](){
        bool ok;
        QString text = QInputDialog::getText(this, tr("Add task"),
                                           tr("New task name:"), QLineEdit::Normal, "New task", &ok);
        if (ok && !text.isEmpty() && !(std::find(subjects.begin(), subjects.end(), text.toStdString()) != subjects.end())) {
            subjectsList->addItem(text);
            qDebug() << "Task added";
        }
        else {
            qDebug() << "Task already in list";
        }
    });

    // remove a task
    connect(remove, &QPushButton::clicked, [=](){
        QList<QListWidgetItem *> itemsToRemove = subjectsList->selectedItems();
        for(int i = 0; i<itemsToRemove.count(); ++i) {
            delete itemsToRemove[i];
        }
    });
}

optionsTab::~optionsTab()
{
    delete ui;
}
