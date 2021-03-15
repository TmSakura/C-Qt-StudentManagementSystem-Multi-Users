#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void updataData_user();

private:
    QSqlDatabase db;
    QSqlQuery *query;
    Ui::Login *ui;

private slots:
    void clickPushButton_enter();
};

#endif // LOGIN_H
