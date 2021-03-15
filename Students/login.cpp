#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    db = QSqlDatabase::database("conn");
    query=new QSqlQuery(db);

    updataData_user();
    connect(ui->pushButton_enter,&QPushButton::clicked,this,&Login::clickPushButton_enter);
}

Login::~Login()
{
    db.close();
    delete ui;
}

void Login::updataData_user()
{
    ui->comboBox_username->clear();
    if(query->exec("select username from user"))
    {
        while (query->next())
        {
            QString username = query->value("username").toString();
            if(!username.isEmpty())
            {
                ui->comboBox_username->addItem(username);
            }
        }
    }
}

void Login::clickPushButton_enter()
{
    query->clear();
    query->exec(QString("select password from user where username = '%1'").arg(ui->comboBox_username->currentText()));
    query->next();
    if(query->value("password").toString()==ui->lineEdit_password->text())
    {
        MainWindow *mainwindow=new MainWindow(ui->comboBox_username->currentText(),this);
        mainwindow->show();
        connect(mainwindow,&MainWindow::exitReturnLogin,this,&Login::updataData_user);
        hide();
    }
    else
    {
        QMessageBox::information(this,"提示","用户名或密码错误");
    }
}
