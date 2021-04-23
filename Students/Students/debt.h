#ifndef DEBT_H
#define DEBT_H

#include <QDialog>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class Debt;
}

class Debt : public QDialog
{
    Q_OBJECT

public:
    explicit Debt(QString number,QString time="",int flag=0,QWidget *parent = nullptr);
    ~Debt();

private slots:
    void clickPushButton();
    void updataDataDictionary();
    void clickPushButton_add1();
    void clickPushButton_add2();
    void clickPushButton_add3();
    void clickPushButton_add4();

signals:
    void needUpdataData();

private:
    Ui::Debt *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString number;
    QString time;
    int flag;
};

#endif // DEBT_H
