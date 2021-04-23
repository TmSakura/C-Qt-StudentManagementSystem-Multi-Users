#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "datadictionary.h"
#include "studentinfo.h"
#include "usercontrol.h"
#include "options.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_CHARTS_USE_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString username, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //tab1
    void updataData_table();
    void updataDataDictonary();
    void clickPushButton_add();
    void clickPushBUtton_editView();
    void clickPushBUtton_delete();
    void clickPushButton_dataDictionary();
    void clickPushButton_user();
    void clickPushButton_search();
    void clickPushButton_importExcel();
    void clickPushButton_exportExcel();

    //tab2
    void updataData_table_2();
    void updataDataDictonary_2();
    void clickPushButton_search_2();

    //tab3
    void updataDataChart();

signals:
    void exitReturnLogin();

private:
    Ui::MainWindow *ui;
    QString username;
    QSqlDatabase db;
    QSqlQuery *query;

    QString read;
    QString write;
    QString remove;
    QString search;
    QString print;
    QString import;
    QString admin;

};
#endif // MAINWINDOW_H
