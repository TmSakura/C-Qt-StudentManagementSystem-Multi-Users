#ifndef SCHOLARSHIP_H
#define SCHOLARSHIP_H

#include <QDialog>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class ScholarShip;
}

class ScholarShip : public QDialog
{
    Q_OBJECT

public:
    explicit ScholarShip(QString number,QString time="",int flag=0,QWidget *parent = nullptr);
    ~ScholarShip();

private slots:
    void clickPushButton();
    void updataDataDictionary();
    void clickPushButton_add1();
    void clickPushButton_add2();

signals:
    void needUpdataData();

private:
    Ui::ScholarShip *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString number;
    QString time;
    int flag;

};

#endif // SCHOLARSHIP_H
