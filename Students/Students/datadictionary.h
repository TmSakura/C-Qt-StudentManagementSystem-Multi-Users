#ifndef DATADICTIONARY_H
#define DATADICTIONARY_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class DataDictionary;
}

class DataDictionary : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataDictionary(QString username,QWidget *parent = nullptr);
    ~DataDictionary();

    void updataData_nation();
    void updataData_political();
    void updataData_province();
    void updataData_city();
    void updataData_university();
    void updataData_college();
    void updataData_profession();
    void updataData_status();
    void updataData_socialStatus();
    void updataData_blood();
    void updataData_eye();
    void updataData_skin();
    void updataData_subject();
    void updataData_year();
    void updataData_semester();
    void updataData_typeOfExam();

private:
    Ui::DataDictionary *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString username;
    QString read;
    QString write;
    QString remove;
    QString search;
    QString print;
    QString import;
    QString admin;

signals:
    void needUpdataData(); //接收者StudentInfo类

private slots:
    void clickPushButton_addNation();
    void clickPushButton_editNation();
    void clickPushButton_deleteNation();

    void clickPushButton_addPolitical();
    void clickPushButton_editPolitical();
    void clickPushButton_deletePolitical();

    void clickPushButton_addProvince();
    void clickPushButton_editProvince();
    void clickPushButton_deleteProvince();

    void clickPushButton_addCity();
    void clickPushButton_editCity();
    void clickPushButton_deleteCity();

    void clickPushButton_addUniversity();
    void clickPushButton_editUniversity();
    void clickPushButton_deleteUniversity();

    void clickPushButton_addCollege();
    void clickPushButton_editCollege();
    void clickPushButton_deleteCollege();

    void clickPushButton_addProfession();
    void clickPushButton_editProfession();
    void clickPushButton_deleteProfession();

    void clickPushButton_addStatus();
    void clickPushButton_editStatus();
    void clickPushButton_deleteStatus();

    void clickPushButton_addSocialStatus();
    void clickPushButton_editSocialStatus();
    void clickPushButton_deleteSocialStatus();

    void clickPushButton_addBlood();
    void clickPushButton_editBlood();
    void clickPushButton_deleteBlood();

    void clickPushButton_addEye();
    void clickPushButton_editEye();
    void clickPushButton_deleteEye();

    void clickPushButton_addSkin();
    void clickPushButton_editSkin();
    void clickPushButton_deleteSkin();

    void clickPushButton_addSubject();
    void clickPushButton_editSubject();
    void clickPushButton_deleteSubject();

    void clickPushButton_addYear();
    void clickPushButton_editYear();
    void clickPushButton_deleteYear();

    void clickPushButton_addSemester();
    void clickPushButton_editSemester();
    void clickPushButton_deleteSemester();

    void clickPushButton_addTypeOfExam();
    void clickPushButton_editTypeOfExam();
    void clickPushButton_deleteTypeOfExam();
};

#endif // DATADICTIONARY_H
