#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <QListWidget>
#include <QTime>
#include <string>
#include <QChar>
#include <QtCharts/QBarSeries>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QList<QListWidgetItem *> itemsToRemove;
private:
    // data to be exported
    int elapsedTime;
    std::string currentTaskName;


    bool isTaskActive = false;


    //obtain the date
    void tdate();

    //export the data
    void dataToFile();

    // format time: takes time (ms) and returns an array containing hours, minutes and seconds
    int* formatTime(int milliseconds);

    //read data for plotting
    void individualPlot(std::string task);

    void multiPlot(); //plots all the time spent

};
#endif // WIDGET_H
