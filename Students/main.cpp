#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL","conn");
    db.setDatabaseName("students");
    db.setUserName("chen");
    db.setPassword("123456");
    bool ok = db.open();
    if(!ok)
    {
        QMessageBox::critical(0, QObject::tr("连接数据库失败！"), db.lastError().text());
        return 1;
    }
    else
    {
        qDebug()<<QObject::tr("连接到数据库。");
    }

    Login login;
    login.show();

    return a.exec();
}
