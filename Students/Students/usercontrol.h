#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "user.h"

namespace Ui {
class UserControl;
}

class UserControl : public QDialog
{
    Q_OBJECT

public:
    explicit UserControl(QString username,QWidget *parent = nullptr);
    ~UserControl();

private slots:
    void updataData_table();
    void clickPushButton_add();
    void clickPushButton_edit();
    void clickPushButton_delete();

private:
    Ui::UserControl *ui;
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
};

#endif // USERCONTROL_H
