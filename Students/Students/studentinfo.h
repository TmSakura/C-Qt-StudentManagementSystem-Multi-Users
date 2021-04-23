#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QFileDialog>
#include "datadictionary.h"
#include "grade.h"
#include "honor.h"
#include "debt.h"
#include "scholarship.h"
#include "punish.h"

namespace Ui {
class StudentInfo;
}

class StudentInfo : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInfo(QString username,QWidget *parent = nullptr,int flag = 0,QString number = "");
    ~StudentInfo();

private slots:

    void clickPushButton_save();
    void clickPushButton_dataDictionary();
    void clickPushButton_addGrade();
    void clickPushButton_editGrade();
    void clickPushButton_deleteGrade();
    void clickPushButton_addHonor();
    void clickPushButton_editHonor();
    void clickPushButton_deleteHonor();
    void clickPushButton_addDebt();
    void clickPushButton_editDebt();
    void clickPushButton_deleteDebt();
    void clickPushButton_addScholarShip();
    void clickPushButton_editScholarShip();
    void clickPushButton_deleteScholarShip();
    void clickPushButton_addPunish();
    void clickPushButton_editPunish();
    void clickPushButton_deletePunish();

    void clickPushButton_openFile1();
    void clickPushButton_openFile2();
    void clickPushButton_openFile3();
    void clickPushButton_openFile4();
    void clickPushButton_saveFile1();
    void clickPushButton_saveFile2();
    void clickPushButton_saveFile3();
    void clickPushButton_saveFile4();
    void clickPushButton_openPhoto();
    void clickPushButton_cancelPhoto();

signals:
    void needUpdataData();

private:
    Ui::StudentInfo *ui;

    QSqlDatabase db;
    QSqlQuery *query;
    QString read;
    QString write;
    QString remove;
    QString search;
    QString print;
    QString import;
    QString admin;

public:
    int flag;               //flag=0表示插入状态，1为编辑/查看状态
    QString number;         //学号
    QString photoPath;      //头像路径
    QString username;
    void updataDataDictonary();
    void initInfoForInsert();
    void initInforForEdit();
    void updataData_grade();
    void updataData_honor();
    void updataData_debt();
    void updataData_scholarShip();
    void updataData_punish();

};

#endif // STUDENTINFO_H
