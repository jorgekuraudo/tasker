#include "statstab.h"
#include "widget.h"
#include "ui_statstab.h"
#include <QPushButton>
#include <QBoxLayout>
#include <fstream>
#include <QtCharts>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

statsTab::statsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statsTab)
{
    ui->setupUi(this);

    //create a widget for a stats tab
    QWidget *stats = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout;

    QPushButton *single = new QPushButton("  Plot");
    single->setIcon(QIcon(":/new/prefix1/18002152251578463634-128.png"));
    single->setIconSize(QSize(32,32));
    single->setToolTip("Shows a plot of all time\nspent on a certain task");
    //QPushButton *multi = new QPushButton("multi task");

    vLayout->setSpacing(10);
    vLayout->addWidget(single);
    //vLayout->addWidget(multi);
    vLayout->addStretch(1);

    stats->setLayout(vLayout);

    //buttons functions
    connect(single, &QPushButton::clicked, [=](){
        std::string taskName = subjectsList->currentItem()->text().toStdString();
        this->individualPlot(taskName);
    });

}

statsTab::~statsTab()
{
    delete ui;
}

std::vector<std::string> statsTab::splitString(std::string string, char delimiter) {
    std::vector<std::string> words;
    std::string currentWord = "";
    for (auto c : string) {
        if(c!=delimiter) {
            currentWord += c;
        } else {
            words.push_back(currentWord);
            currentWord = "";
        }
    }
    words.push_back(currentWord); //string after the last delimiter
    return words;
}

void statsTab::individualPlot(std::string task) {
    //date
    std::vector<std::string> day;
    //time spent
    std::vector<double> timeSpent;
    //read data from file
    std::fstream file;
    file.open("data.txt", std::ios::in);


    std::string line;
    while(std::getline(file, line)) {
        std::vector<std::string> readLine;
        readLine = this->splitString(line, ',');
        std::string dateString = readLine[0] + '/' + readLine[1] + '/' + readLine[2];
        if(readLine[3] == task && !(std::find(day.begin(), day.end(), dateString) != day.end())) {
            timeSpent.push_back(stod(readLine[4]));
            day.push_back(dateString);
            qDebug() << QString::fromStdString(readLine[0] + '/' + readLine[1] + '/' + readLine[2]);
        } else {
            //find the vector index corresponding to dateString
            int index = 0;
            for(auto d : day) {
                if(d == dateString && readLine[3] == task) {
                    timeSpent[index] += stod(readLine[4]);
                } else {
                    ++index;
                }
            }
        }
    }

    //scale timeSpent
    double max = 0; //highest value
    QString yAxisTitle;
    for(auto t : timeSpent) {
        if (t >= max) {
            max = t;
        }
        qDebug() << t << '\t' << max;
    }
    if(max > 3600 * 1000) {
        //in hours
        for(auto &t : timeSpent) {
            t/=(3600 * 1000);
        }
        max/=(3600 * 1000);
        qDebug() << "max is(hr): " << max;
        yAxisTitle = "Hours";
    }
    if(max > 60 * 1000) {
        //in minutes
        for(auto &t : timeSpent) {
            t/=(60 * 1000);
        }
        max/=(60 * 1000);
        qDebug() << "max is(min): " << max;
        yAxisTitle = "Minutes";
    }
    if(max > 1000) {
        //in seconds
        for(auto &t : timeSpent) {
            t/=1000;
        }
        max/=1000;
        qDebug() << "max is(s): " << max;
        yAxisTitle = "Seconds";
    }


    QBarSet *set = new QBarSet(QString::fromStdString(task));
    for(auto v : timeSpent) {
        *set << v;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);

    QBarCategoryAxis *X = new QBarCategoryAxis();
    QStringList dayList;
    for(auto d : day) {
        dayList << QString::fromStdString(d);
        //qDebug() << QString::fromStdString(d);
    }

    X->append(dayList);
    chart->addAxis(X, Qt::AlignBottom);
    series->attachAxis(X);

    QValueAxis *axisY = new QValueAxis();
    max *=1.1; //give some extra space
    axisY->setRange(0,max);
    axisY->setTitleText(yAxisTitle);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);

    chartView->resize(400, 400);
    chartView->show();

}
