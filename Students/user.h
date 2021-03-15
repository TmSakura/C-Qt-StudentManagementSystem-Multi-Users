#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(int flag=0,QString username="",QWidget *parent = nullptr);
    ~User();

private slots:
    void clickPushButton_save();
    void clickPushButton_close();

signals:
    void needUpdataData();

private:
    Ui::User *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    int flag;
    QString username;
};

#endif // USER_H
