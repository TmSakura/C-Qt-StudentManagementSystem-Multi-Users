#ifndef PUNISH_H
#define PUNISH_H

#include <QDialog>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class Punish;
}

class Punish : public QDialog
{
    Q_OBJECT

public:
    explicit Punish(QString number,QString time="",int flag=0,QWidget *parent = nullptr);
    ~Punish();

private slots:
    void clickPushButton();
    void updataDataDictionary();
    void clickPushButton_add1();
    void clickPushButton_add2();

signals:
    void needUpdataData();

private:
    Ui::Punish *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString number;
    QString time;
    int flag;
};


#endif // PUNISH_H
