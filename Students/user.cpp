#include "user.h"
#include "ui_user.h"

User::User(int flag,QString username,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User),flag(flag),username(username)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("conn");
    query=new QSqlQuery(db);

    ui->checkBox_read->setChecked(false);
    ui->checkBox_admin->setChecked(false);
    ui->checkBox_print->setChecked(false);
    ui->checkBox_write->setChecked(false);
    ui->checkBox_delete->setChecked(false);
    ui->checkBox_import->setChecked(false);
    ui->checkBox_search->setChecked(false);

    if(flag==1)
    {
        ui->lineEdit_username->setEnabled(false);

        if(query->exec(QString("SELECT * FROM user WHERE username = '%1'").arg(username)))
        {
            query->first();
            ui->lineEdit_username->setText(query->value(0).toString());
            ui->lineEdit_password->setText(query->value(1).toString());
            if(query->value(2).toString()=="Yes")
                ui->checkBox_read->setChecked(true);
            if(query->value(3).toString()=="Yes")
                ui->checkBox_write->setChecked(true);
            if(query->value(4).toString()=="Yes")
                ui->checkBox_delete->setChecked(true);
            if(query->value(5).toString()=="Yes")
                ui->checkBox_search->setChecked(true);
            if(query->value(6).toString()=="Yes")
                ui->checkBox_print->setChecked(true);
            if(query->value(7).toString()=="Yes")
                ui->checkBox_import->setChecked(true);
            if(query->value(8).toString()=="Yes")
                ui->checkBox_admin->setChecked(true);
        }
    }

    connect(ui->checkBox_admin,&QCheckBox::stateChanged,this,[this](){
        if(ui->checkBox_admin->isChecked())
        {
            ui->checkBox_read->setChecked(true);
            ui->checkBox_write->setChecked(true);
            ui->checkBox_print->setChecked(true);
            ui->checkBox_delete->setChecked(true);
            ui->checkBox_import->setChecked(true);
            ui->checkBox_search->setChecked(true);
        }
    });

    connect(ui->checkBox_read,&QCheckBox::stateChanged,this,[this](){
        if(ui->checkBox_read->isChecked())
            ui->checkBox_search->setChecked(true);
        else
            ui->checkBox_search->setChecked(false);
    });
    connect(ui->checkBox_search,&QCheckBox::stateChanged,this,[this](){
        if(ui->checkBox_search->isChecked())
            ui->checkBox_read->setChecked(true);
        else
            ui->checkBox_read->setChecked(false);
    });
    connect(ui->checkBox_write,&QCheckBox::stateChanged,this,[this](){
        if(ui->checkBox_write->isChecked())
        {
            ui->checkBox_read->setChecked(true);
            ui->checkBox_search->setChecked(true);
        }
    });
    connect(ui->checkBox_delete,&QCheckBox::stateChanged,this,[this](){
        if(ui->checkBox_delete->isChecked())
        {
            ui->checkBox_read->setChecked(true);
            ui->checkBox_search->setChecked(true);
            ui->checkBox_write->setChecked(true);
        }
    });

    connect(ui->pushButton_save,&QPushButton::clicked,this,&User::clickPushButton_save);
    connect(ui->pushButton_close,&QPushButton::clicked,this,&User::clickPushButton_close);
}

User::~User()
{
    delete ui;
}

void User::clickPushButton_save()
{
    QString str;
    QString read,write,remove,search,print,import,admin;
    read=write=remove=search=print=import=admin="No";
    if(ui->checkBox_read->isChecked())
    {
        read="Yes";
    }
    if(ui->checkBox_write->isChecked())
    {
        write="Yes";
    }
    if(ui->checkBox_delete->isChecked())
    {
        remove="Yes";
    }
    if(ui->checkBox_search->isChecked())
    {
        search="Yes";
    }
    if(ui->checkBox_search->isChecked())
    {
        search="Yes";
    }
    if(ui->checkBox_import->isChecked())
    {
        import="Yes";
    }
    if(ui->checkBox_admin->isChecked())
    {
        admin="Yes";
    }
    if(flag==0)
    {
        str=QString("INSERT INTO `user`(`username`, `password`, `read`,`write`, `remove`, `search`,`print`,`import`,`admin`) VALUES "
                    "('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(ui->lineEdit_username->text(),ui->lineEdit_password->text(),read,
                                                                          write,remove,search,print,import,admin);
    }
    else
    {
        str=QString("UPDATE user set password='%1',read='%2',write='%3',remove='%4',search='%5',print='%6',import='%7',admin='%8' WHERE "
                    "username='%9'").arg(ui->lineEdit_password->text(),read,write,remove,
                                         search,print,import,admin,ui->lineEdit_username->text());
    }

    if(query->exec(str))
    {
        emit needUpdataData();
        delete this;
    }
}

void User::clickPushButton_close()
{
    delete this;
}
