#ifndef HONOR_H
#define HONOR_H

#include <QDialog>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class Honor;
}

class Honor : public QDialog
{
    Q_OBJECT

public:
    explicit Honor(QString number,QString time="",int flag=0,QWidget *parent = nullptr);
    ~Honor();

private slots:
    void clickPushButton();
    void updataDataDictionary();
    void clickPushButton_add1();
    void clickPushButton_add2();

signals:
    void needUpdataData();

private:
    Ui::Honor *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString number;
    QString time;
    int flag;
};

#endif // HONOR_H
