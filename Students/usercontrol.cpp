#include "usercontrol.h"
#include "ui_usercontrol.h"

UserControl::UserControl(QString username,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserControl),username(username)
{
    ui->setupUi(this);

    db = QSqlDatabase::database("conn");
    query=new QSqlQuery(db);

    ui->pushButton_add->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);

    //获取权限
    if(query->exec(QString("SELECT * FROM user WHERE username = '%1'").arg(username)))
    {
        query->first();
        read=query->value(2).toString();
        write=query->value(3).toString();
        remove=query->value(4).toString();
        search=query->value(5).toString();
        print=query->value(6).toString();
        import=query->value(7).toString();
        admin=query->value(8).toString();
    }

    if(read=="Yes")
    {
        updataData_table();
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    }
    if(admin=="Yes")
    {
        ui->pushButton_add->setEnabled(true);
        ui->pushButton_edit->setEnabled(true);
        ui->pushButton_delete->setEnabled(true);
        connect(ui->pushButton_add,&QPushButton::clicked,this,&UserControl::clickPushButton_add);
        connect(ui->pushButton_edit,&QPushButton::clicked,this,&UserControl::clickPushButton_edit);
        connect(ui->pushButton_delete,&QPushButton::clicked,this,&UserControl::clickPushButton_delete);
    }
}

UserControl::~UserControl()
{
    delete ui;
}

void UserControl::updataData_table()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"用户"<<"读"<<"写"<<"删除"<<"查找"<<"打印"<<"导出"<<"管理员");

    if(query->exec(QString("SELECT * FROM user")))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget->setItem(count,0,new QTableWidgetItem(query->value(0).toString()));
                ui->tableWidget->setItem(count,1,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget->setItem(count,2,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget->setItem(count,3,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget->setItem(count,4,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget->setItem(count,5,new QTableWidgetItem(query->value(6).toString()));
                ui->tableWidget->setItem(count,6,new QTableWidgetItem(query->value(7).toString()));
                ui->tableWidget->setItem(count,7,new QTableWidgetItem(query->value(8).toString()));
                count++;
                if(!query->next())
                {
                    break;
                }
            }
        }
        else
        {
            return;
        }
    }
}

void UserControl::clickPushButton_add()
{
    User *user=new User();
    user->show();
    user->setAttribute(Qt::WA_QuitOnClose,false);
    user->setAttribute(Qt::WA_DeleteOnClose);
    connect(user,&User::needUpdataData,this,&UserControl::updataData_table);
}

void UserControl::clickPushButton_edit()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QString username=items.at(0)->text();
    User *user=new User(1,username);
    user->show();
    user->setAttribute(Qt::WA_QuitOnClose,false);
    user->setAttribute(Qt::WA_DeleteOnClose);
}

void UserControl::clickPushButton_delete()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QString username=items.at(0)->text();
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除此用户吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        if(username=="admin")
            QMessageBox::information(this,"错误","管理员无法删除!");
        else
        {
            query->exec(QString("DELETE FROM `user` WHERE username = '%1'").arg(username));
            qDebug()<<tr("usercontrol:删除用户成功。");
        }
        updataData_table();
    }
}
