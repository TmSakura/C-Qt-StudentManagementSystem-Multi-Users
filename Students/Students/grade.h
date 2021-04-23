#ifndef GRADE_H
#define GRADE_H

#include <QDialog>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>
namespace Ui {
class Grade;
}

class Grade : public QDialog
{
    Q_OBJECT

public:
    explicit Grade(QString number,QString time="",int flag=0,QWidget *parent = nullptr);
    ~Grade();

private slots:
    void clickPushButton();
    void updataDataDictionary();
    void clickPushButton_add1();
    void clickPushButton_add2();
    void clickPushButton_add3();

signals:
    void needUpdataData();

private:
    Ui::Grade *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString number;
    QString time;
    int flag;

};

#endif // GRADE_H
