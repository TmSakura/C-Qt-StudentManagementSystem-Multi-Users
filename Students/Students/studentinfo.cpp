#include "studentinfo.h"
#include "ui_studentinfo.h"

StudentInfo::StudentInfo(QString username,QWidget *parent,int flag,QString number) :
    QDialog(parent),ui(new Ui::StudentInfo),flag(flag),number(number),photoPath(""),username(username)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("conn");
    query = new QSqlQuery(db);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint);
    setWindowTitle(tr("Students"));


    ui->pushButton_addDebt->setEnabled(false);
    ui->pushButton_addGrade->setEnabled(false);
    ui->pushButton_addHonor->setEnabled(false);
    ui->pushButton_addPunish->setEnabled(false);
    ui->pushButton_addScholarShip->setEnabled(false);
    ui->pushButton_editDebt->setEnabled(false);
    ui->pushButton_editGrade->setEnabled(false);
    ui->pushButton_editHonor->setEnabled(false);
    ui->pushButton_editPunish->setEnabled(false);
    ui->pushButton_editScholarShip->setEnabled(false);
    ui->pushButton_deleteDebt->setEnabled(false);
    ui->pushButton_deleteGrade->setEnabled(false);
    ui->pushButton_deleteHonor->setEnabled(false);
    ui->pushButton_deletePunish->setEnabled(false);
    ui->pushButton_deleteScholarShip->setEnabled(false);
    ui->pushButton_save->setEnabled(false);

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
        ui->tableWidget_grade->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->tableWidget_honor->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_debt->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_scholarShip->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_punish->setSelectionBehavior(QAbstractItemView::SelectRows);
        connect(ui->pushButton_dataDictionary,&QPushButton::clicked,this,&StudentInfo::clickPushButton_dataDictionary);
        updataDataDictonary();
        updataData_grade();
        updataData_honor();
        updataData_debt();
        updataData_scholarShip();
        updataData_punish();

        if(flag == 1 )
        {
            initInforForEdit();
        }
    }
    if(write=="Yes")
    {
        ui->pushButton_save->setEnabled(true);
        ui->pushButton_addDebt->setEnabled(true);
        ui->pushButton_addGrade->setEnabled(true);
        ui->pushButton_addHonor->setEnabled(true);
        ui->pushButton_addPunish->setEnabled(true);
        ui->pushButton_addScholarShip->setEnabled(true);

        connect(ui->pushButton_openFile1,&QPushButton::clicked,this,&StudentInfo::clickPushButton_openFile1);
        connect(ui->pushButton_openFile2,&QPushButton::clicked,this,&StudentInfo::clickPushButton_openFile2);
        connect(ui->pushButton_openFile3,&QPushButton::clicked,this,&StudentInfo::clickPushButton_openFile3);
        connect(ui->pushButton_openFile4,&QPushButton::clicked,this,&StudentInfo::clickPushButton_openFile4);
        connect(ui->pushButton_saveFile1,&QPushButton::clicked,this,&StudentInfo::clickPushButton_saveFile1);
        connect(ui->pushButton_saveFile2,&QPushButton::clicked,this,&StudentInfo::clickPushButton_saveFile2);
        connect(ui->pushButton_saveFile3,&QPushButton::clicked,this,&StudentInfo::clickPushButton_saveFile3);
        connect(ui->pushButton_saveFile4,&QPushButton::clicked,this,&StudentInfo::clickPushButton_saveFile4);
        connect(ui->tableWidget_debt,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_editDebt->setEnabled(true);
            ui->pushButton_deleteDebt->setEnabled(true);
        });
        connect(ui->tableWidget_grade,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_editGrade->setEnabled(true);
            ui->pushButton_deleteGrade->setEnabled(true);
        });
        connect(ui->tableWidget_honor,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_editHonor->setEnabled(true);
            ui->pushButton_deleteHonor->setEnabled(true);
        });
        connect(ui->tableWidget_punish,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_editPunish->setEnabled(true);
            ui->pushButton_deletePunish->setEnabled(true);
        });
        connect(ui->tableWidget_scholarShip,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_editScholarShip->setEnabled(true);
            ui->pushButton_deleteScholarShip->setEnabled(true);
        });
    }
    if(remove=="Yes")
    {
        connect(ui->pushButton_save,&QPushButton::clicked,this,&StudentInfo::clickPushButton_save);

        connect(ui->pushButton_addGrade,&QPushButton::clicked,this,&StudentInfo::clickPushButton_addGrade);
        connect(ui->pushButton_editGrade,&QPushButton::clicked,this,&StudentInfo::clickPushButton_editGrade);
        connect(ui->pushButton_deleteGrade,&QPushButton::clicked,this,&StudentInfo::clickPushButton_deleteGrade);
        connect(ui->pushButton_addHonor,&QPushButton::clicked,this,&StudentInfo::clickPushButton_addHonor);
        connect(ui->pushButton_editHonor,&QPushButton::clicked,this,&StudentInfo::clickPushButton_editHonor);
        connect(ui->pushButton_deleteHonor,&QPushButton::clicked,this,&StudentInfo::clickPushButton_deleteHonor);
        connect(ui->pushButton_addDebt,&QPushButton::clicked,this,&StudentInfo::clickPushButton_addDebt);
        connect(ui->pushButton_editDebt,&QPushButton::clicked,this,&StudentInfo::clickPushButton_editDebt);
        connect(ui->pushButton_deleteDebt,&QPushButton::clicked,this,&StudentInfo::clickPushButton_deleteDebt);
        connect(ui->pushButton_addScholarShip,&QPushButton::clicked,this,&StudentInfo::clickPushButton_addScholarShip);
        connect(ui->pushButton_editScholarShip,&QPushButton::clicked,this,&StudentInfo::clickPushButton_editScholarShip);
        connect(ui->pushButton_deleteScholarShip,&QPushButton::clicked,this,&StudentInfo::clickPushButton_deleteScholarShip);
        connect(ui->pushButton_addPunish,&QPushButton::clicked,this,&StudentInfo::clickPushButton_addPunish);
        connect(ui->pushButton_editPunish,&QPushButton::clicked,this,&StudentInfo::clickPushButton_editPunish);
        connect(ui->pushButton_deletePunish,&QPushButton::clicked,this,&StudentInfo::clickPushButton_deletePunish);
        connect(ui->pushButton_openPhoto,&QPushButton::clicked,this,&StudentInfo::clickPushButton_openPhoto);
        connect(ui->pushButton_cancelPhoto,&QPushButton::clicked,this,&StudentInfo::clickPushButton_cancelPhoto);

        if(flag == 0)
        {
            initInfoForInsert();
        }
    }

    connect(ui->pushButton_exit,&QPushButton::clicked,this,[this](){
        emit needUpdataData();
        parentWidget()->show();
        delete this;
    });

}

StudentInfo::~StudentInfo()
{
    delete ui;
}

void StudentInfo::updataDataDictonary()
{
    if(query->exec("select name from nation"))
    {
        int index=ui->comboBox_nation->currentIndex();
        ui->comboBox_nation->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_nation->addItem(name);
            }
        }
        ui->comboBox_nation->setCurrentIndex(index);
    }
    if(query->exec("select name from political"))
    {
        int index=ui->comboBox_political->currentIndex();
        ui->comboBox_political->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_political->addItem(name);
            }
        }
        ui->comboBox_political->setCurrentIndex(index);
    }
    if(query->exec("select name from province"))
    {
        int index=ui->comboBox_province->currentIndex();
        ui->comboBox_province->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_province->addItem(name);
            }
        }
        ui->comboBox_province->setCurrentIndex(index);
    }
    if(query->exec("select name from city"))
    {
        int index=ui->comboBox_city->currentIndex();
        ui->comboBox_city->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_city->addItem(name);
            }
        }
        ui->comboBox_city->setCurrentIndex(index);
    }
    if(query->exec("select name from university"))
    {
        int index=ui->comboBox_university->currentIndex();
        ui->comboBox_university->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_university->addItem(name);
            }
        }
        ui->comboBox_university->setCurrentIndex(index);
    }
    if(query->exec("select name from college"))
    {
        int index=ui->comboBox_college->currentIndex();
        ui->comboBox_college->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_college->addItem(name);
            }
        }
        ui->comboBox_college->setCurrentIndex(index);
    }
    if(query->exec("select name from profession"))
    {
        int index=ui->comboBox_profession->currentIndex();
        ui->comboBox_profession->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_profession->addItem(name);
            }
        }
        ui->comboBox_profession->setCurrentIndex(index);
    }
    if(query->exec("select name from status"))
    {
        int index=ui->comboBox_status->currentIndex();
        ui->comboBox_status->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_status->addItem(name);
            }
        }
        ui->comboBox_status->setCurrentIndex(index);
    }
    if(query->exec("select name from socialstatus"))
    {
        int index=ui->comboBox_socialStatus->currentIndex();
        ui->comboBox_socialStatus->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_socialStatus->addItem(name);
            }
        }
        ui->comboBox_socialStatus->setCurrentIndex(index);
    }
    if(query->exec("select name from blood"))
    {
        int index=ui->comboBox_blood->currentIndex();
        ui->comboBox_blood->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_blood->addItem(name);
            }
        }
        ui->comboBox_blood->setCurrentIndex(index);
    }
    if(query->exec("select name from eye"))
    {
        int index=ui->comboBox_eye->currentIndex();
        ui->comboBox_eye->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_eye->addItem(name);
            }
        }
        ui->comboBox_eye->setCurrentIndex(index);
    }
    if(query->exec("select name from skin"))
    {
        int index=ui->comboBox_skin->currentIndex();
        ui->comboBox_skin->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_skin->addItem(name);
            }
        }
        ui->comboBox_skin->setCurrentIndex(index);
    }
}

void StudentInfo::clickPushButton_save()
{
    query->clear();
    QString fatherWork(""),motherWork("");
    if(ui->checkBox_father_workToTheState->isChecked())
    {
        fatherWork=tr("为国家工作");
    }
    else if(ui->checkBox_father_selfEmployed->isChecked())
    {
        fatherWork=tr("自由职业者");
    }
    if(ui->checkBox_mother_workToTheState->isChecked())
    {
        motherWork=tr("为国家工作");
    }
    else if(ui->checkBox_mother_selfEmployed->isChecked())
    {
        motherWork=tr("自由职业者");
    }
    if(flag == 0)
    {
        query->exec(QString("SELECT * FROM studentinfo WHERE number = '%1'").arg(ui->lineEdit_number->text()));
        if(query->last())
        {
            QMessageBox::information(this,"错误","学号重复!");
            return;
        }
        if(query->exec(QString("INSERT INTO studentinfo (`name`,`number`,`sex`,`nation`,`political`,`birthData`,`birthPlace`,`idCard`,"
                               "`province`,`city`,`university`, `college`, `profession`, `status`, `dataOfAdmission`, `dataOfGraduation`,"
                               "`homeAddress`,`phone`,`socialStatus`,`blood`,`eye`,`skin`,`fatherName`,`fatherWork`,`motherName`,`motherWork`,"
                               "`parentOtherInformation`,`photo`,`otherInterest`) VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10',"
                               "'%11','%12','%13','%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26','%27','%28',"
                               "'%29')").arg(ui->lineEdit_name->text(),ui->lineEdit_number->text(),ui->comboBox_sex->currentText(),
                                             ui->comboBox_nation->currentText(),ui->comboBox_political->currentText(),ui->dateEdit_birthData->text(),
                                             ui->lineEdit_birthPlace->text(),ui->lineEdit_idCard->text(),ui->comboBox_province->currentText(),
                                             ui->comboBox_city->currentText(),ui->comboBox_university->currentText(),ui->comboBox_college->currentText(),
                                             ui->comboBox_profession->currentText(),ui->comboBox_status->currentText(),ui->dateEdit_dataOfAdmission->text(),
                                             ui->dateEdit_dataOfGraduation->text(),ui->lineEdit_homeAddress->text(),ui->lineEdit_phone->text(),
                                             ui->comboBox_socialStatus->currentText(),ui->comboBox_blood->currentText(),ui->comboBox_eye->currentText(),
                                             ui->comboBox_skin->currentText(),ui->lineEdit_fatherName->text(),fatherWork,ui->lineEdit_motherName->text(),motherWork,
                                             ui->textEdit_parentsOtherInformation->toPlainText(),photoPath,ui->textEdit_otherInterest->toPlainText())))
        {
            QMessageBox::information(this,"提示","插入数据成功。");
            emit needUpdataData();
        }
        else
        {
            QMessageBox::information(this,"提示","插入失败，有项为空。");
        }
    }
    else if(flag == 1)
    {
        query->clear();
        if(query->exec(QString("UPDATE studentinfo SET name='%1',number='%2',sex='%3',nation='%4',political='%5',birthData='%6',birthPlace='%7',idCard='%8',"
                               "province='%9',city='%10',university='%11',college='%12',profession='%13',status='%14',dataOfAdmission='%15',dataOfGraduation='%16',"
                               "homeAddress='%17',phone='%18',socialStatus='%19',blood='%20',eye='%21',skin='%22',fatherName='%23',fatherWork='%24',motherName='%25',motherWork='%26',"
                               "parentOtherInformation='%27',photo='%28',otherInterest='%29' WHERE number = '%30'").arg(ui->lineEdit_name->text(),ui->lineEdit_number->text(),ui->comboBox_sex->currentText(),
                                                                                                                        ui->comboBox_nation->currentText(),ui->comboBox_political->currentText(),ui->dateEdit_birthData->text(),
                                                                                                                        ui->lineEdit_birthPlace->text(),ui->lineEdit_idCard->text(),ui->comboBox_province->currentText(),
                                                                                                                        ui->comboBox_city->currentText(),ui->comboBox_university->currentText(),ui->comboBox_college->currentText(),
                                                                                                                        ui->comboBox_profession->currentText(),ui->comboBox_status->currentText(),ui->dateEdit_dataOfAdmission->text(),
                                                                                                                        ui->dateEdit_dataOfGraduation->text(),ui->lineEdit_homeAddress->text(),ui->lineEdit_phone->text(),
                                                                                                                        ui->comboBox_socialStatus->currentText(),ui->comboBox_blood->currentText(),ui->comboBox_eye->currentText(),
                                                                                                                        ui->comboBox_skin->currentText(),ui->lineEdit_fatherName->text(),fatherWork,ui->lineEdit_motherName->text(),motherWork,
                                                                                                                        ui->textEdit_parentsOtherInformation->toPlainText(),photoPath,ui->textEdit_otherInterest->toPlainText(),ui->lineEdit_number->text())))
        {
            QMessageBox::information(this,"提示","保存数据成功。");
            emit needUpdataData();
        }
        else
        {
            QMessageBox::information(this,"提示","保存失败。");
        }
    }
}

void StudentInfo::clickPushButton_dataDictionary()
{
    DataDictionary *datadictionary = new DataDictionary(username,this);
    datadictionary->show();
    datadictionary->setAttribute(Qt::WA_QuitOnClose,false);
    datadictionary->setAttribute(Qt::WA_DeleteOnClose);
    connect(datadictionary,&DataDictionary::needUpdataData,this,&StudentInfo::updataDataDictonary);
}

void StudentInfo::clickPushButton_addGrade()
{
    Grade *grade=new Grade(number);
    connect(grade,&Grade::needUpdataData,this,&StudentInfo::updataData_grade);
    grade->setAttribute(Qt::WA_QuitOnClose,false);
    grade->setAttribute(Qt::WA_DeleteOnClose);
    grade->show();
}

void StudentInfo::clickPushButton_editGrade()
{
    ui->tableWidget_grade->showColumn(5);
    QList<QTableWidgetItem*> items = ui->tableWidget_grade->selectedItems();
    Grade *grade=new Grade(number,items.at(5)->text(),1);
    connect(grade,&Grade::needUpdataData,this,&StudentInfo::updataData_grade);
    grade->setAttribute(Qt::WA_QuitOnClose,false);
    grade->setAttribute(Qt::WA_DeleteOnClose);
    grade->show();
    ui->tableWidget_grade->hideColumn(5);
}

void StudentInfo::clickPushButton_deleteGrade()
{
    ui->tableWidget_grade->showColumn(5);
    QList<QTableWidgetItem*> items = ui->tableWidget_grade->selectedItems();
    QString time=items.at(5)->text();
    ui->tableWidget_grade->hideColumn(5);
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        if(query->exec(QString("DELETE FROM `grade` WHERE time = '%1'").arg(time)))
        {
            qDebug()<<tr("StudentInfo：删除成绩成功。");
        }
        updataData_grade();
    }
    ui->pushButton_editGrade->setEnabled(false);
    ui->pushButton_deleteGrade->setEnabled(false);
}

void StudentInfo::clickPushButton_addHonor()
{
    Honor *honor=new Honor(number);
    connect(honor,&Honor::needUpdataData,this,&StudentInfo::updataData_honor);
    honor->setAttribute(Qt::WA_QuitOnClose,false);
    honor->setAttribute(Qt::WA_DeleteOnClose);
    honor->show();
}

void StudentInfo::clickPushButton_editHonor()
{
    ui->tableWidget_honor->showColumn(5);
    QList<QTableWidgetItem*> items = ui->tableWidget_honor->selectedItems();
    Honor *honor=new Honor(number,items.at(5)->text(),1);
    connect(honor,&Honor::needUpdataData,this,&StudentInfo::updataData_honor);
    honor->setAttribute(Qt::WA_QuitOnClose,false);
    honor->setAttribute(Qt::WA_DeleteOnClose);
    honor->show();
    ui->tableWidget_honor->hideColumn(5);
}

void StudentInfo::clickPushButton_deleteHonor()
{
    ui->tableWidget_honor->showColumn(5);
    QList<QTableWidgetItem*> items = ui->tableWidget_honor->selectedItems();
    QString time=items.at(5)->text();
    ui->tableWidget_honor->hideColumn(5);
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        if(query->exec(QString("DELETE FROM `honor` WHERE time = '%1'").arg(time)))
        {
            qDebug()<<tr("StudentInfo：删除获奖信息成功。");
        }
        updataData_honor();
    }
    ui->pushButton_editHonor->setEnabled(false);
    ui->pushButton_deleteHonor->setEnabled(false);
}

void StudentInfo::clickPushButton_addDebt()
{
    Debt *debt=new Debt(number);
    connect(debt,&Debt::needUpdataData,this,&StudentInfo::updataData_debt);
    debt->setAttribute(Qt::WA_QuitOnClose,false);
    debt->setAttribute(Qt::WA_DeleteOnClose);
    debt->show();
}

void StudentInfo::clickPushButton_editDebt()
{
    ui->tableWidget_debt->showColumn(6);
    QList<QTableWidgetItem*> items = ui->tableWidget_debt->selectedItems();
    Debt *debt=new Debt(number,items.at(6)->text(),1);
    connect(debt,&Debt::needUpdataData,this,&StudentInfo::updataData_debt);
    debt->setAttribute(Qt::WA_QuitOnClose,false);
    debt->setAttribute(Qt::WA_DeleteOnClose);
    debt->show();
    ui->tableWidget_debt->hideColumn(6);
}

void StudentInfo::clickPushButton_deleteDebt()
{
    ui->tableWidget_debt->showColumn(6);
    QList<QTableWidgetItem*> items = ui->tableWidget_debt->selectedItems();
    QString time=items.at(6)->text();
    ui->tableWidget_debt->hideColumn(6);
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        if(query->exec(QString("DELETE FROM `debt` WHERE time = '%1'").arg(time)))
        {
            qDebug()<<tr("StudentInfo：删除挂科信息成功。");
        }
        updataData_debt();
    }
    ui->pushButton_editDebt->setEnabled(false);
    ui->pushButton_deleteDebt->setEnabled(false);
}

void StudentInfo::clickPushButton_addScholarShip()
{
    ScholarShip *scholarship=new ScholarShip(number);
    connect(scholarship,&ScholarShip::needUpdataData,this,&StudentInfo::updataData_scholarShip);
    scholarship->setAttribute(Qt::WA_QuitOnClose,false);
    scholarship->setAttribute(Qt::WA_DeleteOnClose);
    scholarship->show();
}

void StudentInfo::clickPushButton_editScholarShip()
{
    ui->tableWidget_scholarShip->showColumn(4);
    QList<QTableWidgetItem*> items = ui->tableWidget_scholarShip->selectedItems();
    ScholarShip *scholarship=new ScholarShip(number,items.at(4)->text(),1);
    connect(scholarship,&ScholarShip::needUpdataData,this,&StudentInfo::updataData_scholarShip);
    scholarship->setAttribute(Qt::WA_QuitOnClose,false);
    scholarship->setAttribute(Qt::WA_DeleteOnClose);
    scholarship->show();
    ui->tableWidget_scholarShip->hideColumn(4);
}

void StudentInfo::clickPushButton_deleteScholarShip()
{
    ui->tableWidget_scholarShip->showColumn(4);
    QList<QTableWidgetItem*> items = ui->tableWidget_scholarShip->selectedItems();
    QString time=items.at(4)->text();
    ui->tableWidget_scholarShip->hideColumn(4);
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        if(query->exec(QString("DELETE FROM `scholarship` WHERE time = '%1'").arg(time)))
        {
            qDebug()<<tr("StudentInfo：删除奖学金信息成功。");
        }
        updataData_scholarShip();
    }
    ui->pushButton_editScholarShip->setEnabled(false);
    ui->pushButton_deleteScholarShip->setEnabled(false);
}

void StudentInfo::clickPushButton_addPunish()
{
    Punish *punish=new Punish(number);
    connect(punish,&Punish::needUpdataData,this,&StudentInfo::updataData_punish);
    punish->setAttribute(Qt::WA_QuitOnClose,false);
    punish->setAttribute(Qt::WA_DeleteOnClose);
    punish->show();
}

void StudentInfo::clickPushButton_editPunish()
{
    ui->tableWidget_punish->showColumn(6);
    QList<QTableWidgetItem*> items = ui->tableWidget_punish->selectedItems();
    Punish *punish=new Punish(number,items.at(6)->text(),1);
    connect(punish,&Punish::needUpdataData,this,&StudentInfo::updataData_punish);
    punish->setAttribute(Qt::WA_QuitOnClose,false);
    punish->setAttribute(Qt::WA_DeleteOnClose);
    punish->show();
    ui->tableWidget_punish->hideColumn(6);
}

void StudentInfo::clickPushButton_deletePunish()
{
    ui->tableWidget_punish->showColumn(6);
    QList<QTableWidgetItem*> items = ui->tableWidget_punish->selectedItems();
    QString time=items.at(6)->text();
    ui->tableWidget_punish->hideColumn(6);
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        if(query->exec(QString("DELETE FROM `punish` WHERE time = '%1'").arg(time)))
        {
            qDebug()<<tr("StudentInfo：删除处分成功。");
        }
        updataData_punish();
    }
    ui->pushButton_editPunish->setEnabled(false);
    ui->pushButton_deletePunish->setEnabled(false);
}

void StudentInfo::clickPushButton_openFile1()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择文件"));
    fileDialog->setDirectory(ui->lineEdit_file1->text());
    fileDialog->setNameFilter("*.*");
    if (fileDialog->exec())
    {
        ui->lineEdit_file1->setText(fileDialog->selectedFiles()[0]);
    }
}

void StudentInfo::clickPushButton_openFile2()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择文件"));
    fileDialog->setDirectory(ui->lineEdit_file2->text());
    fileDialog->setNameFilter("*.*");
    if (fileDialog->exec())
    {
        ui->lineEdit_file2->setText(fileDialog->selectedFiles()[0]);
    }
}

void StudentInfo::clickPushButton_openFile3()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择文件"));
    fileDialog->setDirectory(ui->lineEdit_file3->text());
    fileDialog->setNameFilter("*.*");
    if (fileDialog->exec())
    {
        ui->lineEdit_file3->setText(fileDialog->selectedFiles()[0]);
    }
}

void StudentInfo::clickPushButton_openFile4()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择文件"));
    fileDialog->setDirectory(ui->lineEdit_file4->text());
    fileDialog->setNameFilter("*.*");
    if (fileDialog->exec())
    {
        ui->lineEdit_file4->setText(fileDialog->selectedFiles()[0]);
    }
}

void StudentInfo::clickPushButton_saveFile1()
{
    QString str;
    query->exec(QString("SELECT * FROM file WHERE number = '%1'"));
    if(query->last()!=0)
    {
        str=QString("UPDATE `file` SET `file1`='%1',`file2`='%2',`file3`='%3',`file4`='%4' WHERE number = '%5'").
                arg(ui->lineEdit_file1->text(),"","","",number);
    }
    else
    {
        str=QString("INSERT INTO `file`(`number`, `file1`, `file2`, `file3`, `file4`) VALUES ('%1','%2','%3','%4','%5')").
                arg(number,ui->lineEdit_file1->text(),"","","");
    }
    query->clear();
    if(query->exec(str))
    {
        QMessageBox::information(this,"提示","保存文件成功");
    }
}

void StudentInfo::clickPushButton_saveFile2()
{
    QString str;
    query->exec(QString("SELECT * FROM file WHERE number = '%1'"));
    if(query->last()!=0)
    {
        str=QString("UPDATE `file` SET `file1`='%1',`file2`='%2',`file3`='%3',`file4`='%4' WHERE number = '%5'").
                arg("",ui->lineEdit_file2->text(),"","",number);
    }
    else
    {
        str=QString("INSERT INTO `file`(`number`, `file1`, `file2`, `file3`, `file4`) VALUES ('%1','%2','%3','%4','%5')").
                arg(number,"",ui->lineEdit_file2->text(),"","");
    }
    query->clear();
    if(query->exec(str))
    {
        QMessageBox::information(this,"提示","保存文件成功");
    }
}

void StudentInfo::clickPushButton_saveFile3()
{
    QString str;
    query->exec(QString("SELECT * FROM file WHERE number = '%1'"));
    if(query->last()!=0)
    {
        str=QString("UPDATE `file` SET `file1`='%1',`file2`='%2',`file3`='%3',`file4`='%4' WHERE number = '%5'").
                arg("","",ui->lineEdit_file3->text(),"",number);
    }
    else
    {
        str=QString("INSERT INTO `file`(`number`, `file1`, `file2`, `file3`, `file4`) VALUES ('%1','%2','%3','%4','%5')").
                arg(number,"","",ui->lineEdit_file3->text(),"");
    }
    query->clear();
    if(query->exec(str))
    {
        QMessageBox::information(this,"提示","保存文件成功");
    }
}

void StudentInfo::clickPushButton_saveFile4()
{
    QString str;
    query->exec(QString("SELECT * FROM file WHERE number = '%1'"));
    if(query->last()!=0)
    {
        str=QString("UPDATE `file` SET `file1`='%1',`file2`='%2',`file3`='%3',`file4`='%4' WHERE number = '%5'").
                arg("","","",ui->lineEdit_file4->text(),number);
    }
    else
    {
        str=QString("INSERT INTO `file`(`number`, `file1`, `file2`, `file3`, `file4`) VALUES ('%1','%2','%3','%4','%5')").
                arg(number,"","","",ui->lineEdit_file4->text());
    }
    query->clear();
    if(query->exec(str))
    {
        QMessageBox::information(this,"提示","保存文件成功");
    }
}

void StudentInfo::clickPushButton_openPhoto()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开文件"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));

    if (fileDialog->exec())
    {
        photoPath= fileDialog->selectedFiles()[0];
        qDebug()<<photoPath;
        //ui->frame_photo->setStyleSheet("background-image: url(:/images/open.png)");
    }
}

void StudentInfo::clickPushButton_cancelPhoto()
{
    photoPath="";
    ui->frame_photo->setStyleSheet("background-image: url()");
}

void StudentInfo::initInfoForInsert()
{
    ui->comboBox_eye->setCurrentIndex(-1);
    ui->comboBox_sex->setCurrentIndex(-1);
    ui->comboBox_city->setCurrentIndex(-1);
    ui->comboBox_skin->setCurrentIndex(-1);
    ui->comboBox_blood->setCurrentIndex(-1);
    ui->comboBox_nation->setCurrentIndex(-1);
    ui->comboBox_status->setCurrentIndex(-1);
    ui->comboBox_college->setCurrentIndex(-1);
    ui->comboBox_province->setCurrentIndex(-1);
    ui->comboBox_political->setCurrentIndex(-1);
    ui->comboBox_profession->setCurrentIndex(-1);
    ui->comboBox_university->setCurrentIndex(-1);
    ui->comboBox_socialStatus->setCurrentIndex(-1);
    ui->dateEdit_birthData->setDate(QDate::currentDate());
    ui->dateEdit_dataOfAdmission->setDate(QDate::currentDate());
    ui->dateEdit_dataOfGraduation->setDate(QDate::currentDate());
    ui->tabWidget->setEnabled(false);
    ui->groupBox_file->setEnabled(false);
}

void StudentInfo::initInforForEdit()
{
    query->exec(QString("SELECT * FROM studentinfo WHERE number = '%1'").arg(number));
    query->first();
    ui->lineEdit_name->setText(query->value(0).toString());
    ui->lineEdit_number->setText(query->value(1).toString());
    ui->comboBox_sex->setCurrentText(query->value(2).toString());
    ui->comboBox_nation->setCurrentText(query->value(3).toString());
    ui->comboBox_political->setCurrentText(query->value(4).toString());
    ui->dateEdit_birthData->setDate(QDate::fromString(query->value(5).toString(),"d/M/yyyy"));
    ui->lineEdit_birthPlace->setText(query->value(6).toString());
    ui->lineEdit_idCard->setText(query->value(7).toString());
    ui->comboBox_province->setCurrentText(query->value(8).toString());
    ui->comboBox_city->setCurrentText(query->value(9).toString());
    ui->comboBox_university->setCurrentText(query->value(10).toString());
    ui->comboBox_college->setCurrentText(query->value(11).toString());
    ui->comboBox_profession->setCurrentText(query->value(12).toString());
    ui->comboBox_status->setCurrentText(query->value(13).toString());
    ui->dateEdit_dataOfAdmission->setDate(QDate::fromString(query->value(14).toString(),"d/M/yyyy"));
    ui->dateEdit_dataOfGraduation->setDate(QDate::fromString(query->value(15).toString(),"d/M/yyyy"));
    ui->lineEdit_homeAddress->setText(query->value(16).toString());
    ui->lineEdit_phone->setText(query->value(17).toString());
    ui->comboBox_socialStatus->setCurrentText(query->value(18).toString());
    ui->comboBox_blood->setCurrentText(query->value(19).toString());
    ui->comboBox_eye->setCurrentText(query->value(20).toString());
    ui->comboBox_skin->setCurrentText(query->value(21).toString());
    ui->lineEdit_fatherName->setText(query->value(22).toString());
    if(query->value(23).toString()=="自由职业者")
        ui->checkBox_father_selfEmployed->setChecked(true);
    else
        ui->checkBox_father_workToTheState->setChecked(true);
    ui->lineEdit_motherName->setText(query->value(24).toString());
    if(query->value(25).toString()=="自由职业者")
        ui->checkBox_mother_selfEmployed->setChecked(true);
    else
        ui->checkBox_mother_workToTheState->setChecked(true);
    ui->textEdit_parentsOtherInformation->setText(query->value(26).toString());
    ui->textEdit_otherInterest->setText(query->value(28).toString());

    ui->frame_photo->setStyleSheet(QString("background-image: url(%1)").arg(photoPath));

    query->clear();
    query->exec(QString("SELECT * FROM file WHERE number = '%1'").arg(number));
    if(query->last()!=false)
    {
        query->first();
        ui->lineEdit_file1->setText(query->value(1).toString());
        ui->lineEdit_file2->setText(query->value(2).toString());
        ui->lineEdit_file3->setText(query->value(3).toString());
        ui->lineEdit_file4->setText(query->value(4).toString());
    }
}

void StudentInfo::updataData_grade()
{
    ui->tableWidget_grade->clear();
    ui->tableWidget_grade->setColumnCount(6);
    ui->tableWidget_grade->setHorizontalHeaderLabels(QStringList()<<"科目"<<"分数"<<"日期"<<"学期"<<"年份"<<"时间");

    ui->tableWidget_grade->hideColumn(5);

    if(query->exec(QString("SELECT * FROM grade WHERE number = '%1'").arg(number)))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_grade->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_grade->setItem(count,0,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_grade->setItem(count,1,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_grade->setItem(count,2,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_grade->setItem(count,3,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_grade->setItem(count,4,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget_grade->setItem(count,5,new QTableWidgetItem(query->value(6).toString()));
                count++;
                if(!query->next())
                {
                    break;
                }
            }
        }
        else
        {
            ui->tableWidget_grade->setRowCount(0);//为了删除空的一行
            return;
        }
    }
}

void StudentInfo::updataData_honor()
{
    ui->tableWidget_honor->clear();
    ui->tableWidget_honor->setColumnCount(6);
    ui->tableWidget_honor->setHorizontalHeaderLabels(QStringList()<<"名称"<<"级别"<<"日期"<<"学期"<<"年份"<<"时间");

    ui->tableWidget_honor->hideColumn(5);

    if(query->exec(QString("SELECT * FROM honor WHERE number = '%1'").arg(number)))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_honor->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_honor->setItem(count,0,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_honor->setItem(count,1,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_honor->setItem(count,2,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_honor->setItem(count,3,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_honor->setItem(count,4,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget_honor->setItem(count,5,new QTableWidgetItem(query->value(6).toString()));
                count++;
                if(!query->next())
                {
                    break;
                }
            }
        }
        else
        {
            ui->tableWidget_honor->setRowCount(0);//为了删除空的一行
            return;
        }
    }
}

void StudentInfo::updataData_debt()
{
    ui->tableWidget_debt->clear();
    ui->tableWidget_debt->setColumnCount(7);
    ui->tableWidget_debt->setHorizontalHeaderLabels(QStringList()<<"科目"<<"分数"<<"类型"<<"日期"<<"学期"<<"年份"<<"时间");

    ui->tableWidget_debt->hideColumn(6);

    if(query->exec(QString("SELECT * FROM debt WHERE number = '%1'").arg(number)))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_debt->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_debt->setItem(count,0,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_debt->setItem(count,1,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_debt->setItem(count,2,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_debt->setItem(count,3,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_debt->setItem(count,4,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget_debt->setItem(count,5,new QTableWidgetItem(query->value(6).toString()));
                ui->tableWidget_debt->setItem(count,6,new QTableWidgetItem(query->value(7).toString()));
                count++;
                if(!query->next())
                {
                    break;
                }
            }
        }
        else
        {
            ui->tableWidget_debt->setRowCount(0);//为了删除空的一行
            return;
        }
    }
}

void StudentInfo::updataData_scholarShip()
{
    ui->tableWidget_scholarShip->clear();
    ui->tableWidget_scholarShip->setColumnCount(5);
    ui->tableWidget_scholarShip->setHorizontalHeaderLabels(QStringList()<<"金额"<<"日期"<<"学期"<<"年份"<<"时间");

    ui->tableWidget_scholarShip->hideColumn(4);

    if(query->exec(QString("SELECT * FROM scholarship WHERE number = '%1'").arg(number)))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_scholarShip->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_scholarShip->setItem(count,0,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_scholarShip->setItem(count,1,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_scholarShip->setItem(count,2,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_scholarShip->setItem(count,3,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_scholarShip->setItem(count,4,new QTableWidgetItem(query->value(5).toString()));
                count++;
                if(!query->next())
                {
                    break;
                }
            }
        }
        else
        {
            ui->tableWidget_scholarShip->setRowCount(0);//为了删除空的一行
            return;
        }
    }
}

void StudentInfo::updataData_punish()
{
    ui->tableWidget_punish->clear();
    ui->tableWidget_punish->setColumnCount(7);
    ui->tableWidget_punish->setHorizontalHeaderLabels(QStringList()<<"原因"<<"处理"<<"日期"<<"学期"<<"年份"<<"结果"<<"时间");

    ui->tableWidget_punish->hideColumn(6);

    if(query->exec(QString("SELECT * FROM punish WHERE number = '%1'").arg(number)))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_punish->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_punish->setItem(count,0,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_punish->setItem(count,1,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_punish->setItem(count,2,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_punish->setItem(count,3,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_punish->setItem(count,4,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget_punish->setItem(count,5,new QTableWidgetItem(query->value(6).toString()));
                ui->tableWidget_punish->setItem(count,6,new QTableWidgetItem(query->value(7).toString()));
                count++;
                if(!query->next())
                {
                    break;
                }
            }
        }
        else
        {
            ui->tableWidget_punish->setRowCount(0); //为了删除空的一行
            return;
        }
    }
}






