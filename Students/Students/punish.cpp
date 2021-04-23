#include "punish.h"
#include "ui_punish.h"

Punish::Punish(QString number,QString time,int flag,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Punish),number(number),time(time),flag(flag)
{
    ui->setupUi(this);

    db = QSqlDatabase::database("conn");
    query=new QSqlQuery(db);

    ui->checkBox->setChecked(true);
    ui->dateEdit->setEnabled(false);
    ui->dateEdit->setDate(QDate::currentDate());

    ui->comboBox_semester->setCurrentIndex(-1);
    ui->comboBox_year->setCurrentIndex(-1);

    connect(ui->pushButton_add1,&QPushButton::clicked,this,&Punish::clickPushButton_add1);
    connect(ui->pushButton_add2,&QPushButton::clicked,this,&Punish::clickPushButton_add2);
    connect(ui->pushButton,&QPushButton::clicked,this,&Punish::clickPushButton);
    connect(ui->checkBox,&QCheckBox::stateChanged,this,[this](){
        if(ui->checkBox->isChecked())
            ui->dateEdit->setEnabled(false);
        else
            ui->dateEdit->setEnabled(true);
    });

    updataDataDictionary();

    if(flag==1)
    {
        if(query->exec(QString("SELECT * FROM punish WHERE time = '%1'").arg(time)))
        {
            query->first();
            ui->lineEdit_reason->setText(query->value(1).toString());
            ui->lineEdit_handling->setText(query->value(2).toString());
            if(query->value(3).toString()!="")
            {
                ui->checkBox->setChecked(false);
                ui->dateEdit->setDate(QDate::fromString(query->value(3).toString(),"d/M/yyyy"));
            }
            ui->comboBox_semester->setCurrentText(query->value(4).toString());
            ui->comboBox_year->setCurrentText(query->value(5).toString());;
            ui->lineEdit_result->setText(query->value(6).toString());
        }
    }
}

Punish::~Punish()
{
    delete ui;
}

void Punish::clickPushButton()
{
    QString data;
    if(ui->checkBox->isChecked())
        data="";
    else
        data=ui->dateEdit->text();
    QString str;
    if(flag==0)
    {
        str=QString("INSERT INTO `punish`(`number`, `reason`, `handling`,`date`, `semester`, `year`,`result`, `time`) VALUES "
                    "('%1','%2','%3','%4','%5','%6','%7','%8')").arg(number,ui->lineEdit_reason->text(),ui->lineEdit_handling->text(),
                                                          data,ui->comboBox_semester->currentText(),ui->comboBox_year->currentText(),
                                                                     ui->lineEdit_result->text(),QDateTime::currentDateTime().toString());
    }
    else
    {
        str=QString("UPDATE punish set reason='%1',handling='%2',date='%3',semester='%4',year='%5',result='%6' WHERE "
                    "time='%7'").arg(ui->lineEdit_reason->text(),ui->lineEdit_handling->text(),data,ui->comboBox_semester->currentText(),
                                     ui->comboBox_year->currentText(),ui->lineEdit_result->text(),time);
    }

    if(query->exec(str))
    {
        emit needUpdataData();
        delete this;
    }
    else
    {
        qDebug()<<str;
        QMessageBox::information(this,"提示","保存失败。");
    }
}

void Punish::updataDataDictionary()
{
    if(query->exec("select name from semester"))
    {
        int index=ui->comboBox_semester->currentIndex();
        ui->comboBox_semester->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_semester->addItem(name);
            }
        }
        ui->comboBox_semester->setCurrentIndex(index);
    }
    if(query->exec("select name from year"))
    {
        int index=ui->comboBox_year->currentIndex();
        ui->comboBox_year->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_year->addItem(name);
            }
        }
        ui->comboBox_year->setCurrentIndex(index);
    }
}

void Punish::clickPushButton_add1()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加学期"),tr("学期:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `semester` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("Punish:添加学期成功。");
        }
        updataDataDictionary();
    }
}

void Punish::clickPushButton_add2()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加年份"),tr("年份:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `year` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("Punish:添加年份成功。");
        }
        updataDataDictionary();
    }
}
