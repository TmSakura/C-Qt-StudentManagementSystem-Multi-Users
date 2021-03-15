#include "datadictionary.h"
#include "ui_datadictionary.h"

DataDictionary::DataDictionary(QString username,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataDictionary),username(username)
{
    ui->setupUi(this);

    db = QSqlDatabase::database("conn");
    query = new QSqlQuery(db);

    ui->pushButton_addNation->setEnabled(false);
    ui->pushButton_editNation->setEnabled(false);
    ui->pushButton_deleteNation->setEnabled(false);
    ui->pushButton_addPolitical->setEnabled(false);
    ui->pushButton_editPolitical->setEnabled(false);
    ui->pushButton_deletePolitical->setEnabled(false);
    ui->pushButton_addProvince->setEnabled(false);
    ui->pushButton_editProvince->setEnabled(false);
    ui->pushButton_deleteProvince->setEnabled(false);
    ui->pushButton_addCity->setEnabled(false);
    ui->pushButton_editCity->setEnabled(false);
    ui->pushButton_deleteCity->setEnabled(false);
    ui->pushButton_addUniversity->setEnabled(false);
    ui->pushButton_editUniversity->setEnabled(false);
    ui->pushButton_deleteUniversity->setEnabled(false);
    ui->pushButton_addCollege->setEnabled(false);
    ui->pushButton_editCollege->setEnabled(false);
    ui->pushButton_deleteCollege->setEnabled(false);
    ui->pushButton_addProfession->setEnabled(false);
    ui->pushButton_editProfession->setEnabled(false);
    ui->pushButton_deleteProfession->setEnabled(false);
    ui->pushButton_addStatus->setEnabled(false);
    ui->pushButton_editStatus->setEnabled(false);
    ui->pushButton_deleteStatus->setEnabled(false);
    ui->pushButton_addSocialStatus->setEnabled(false);
    ui->pushButton_editSocialStatus->setEnabled(false);
    ui->pushButton_deleteSocialStatus->setEnabled(false);
    ui->pushButton_addBlood->setEnabled(false);
    ui->pushButton_editBlood->setEnabled(false);
    ui->pushButton_deleteBlood->setEnabled(false);
    ui->pushButton_addEye->setEnabled(false);
    ui->pushButton_editEye->setEnabled(false);
    ui->pushButton_deleteEye->setEnabled(false);
    ui->pushButton_addSkin->setEnabled(false);
    ui->pushButton_editSkin->setEnabled(false);
    ui->pushButton_deleteSkin->setEnabled(false);
    ui->pushButton_addSubject->setEnabled(false);
    ui->pushButton_editSubject->setEnabled(false);
    ui->pushButton_deleteSubject->setEnabled(false);
    ui->pushButton_addYear->setEnabled(false);
    ui->pushButton_editYear->setEnabled(false);
    ui->pushButton_deleteYear->setEnabled(false);
    ui->pushButton_addSemester->setEnabled(false);
    ui->pushButton_editSemester->setEnabled(false);
    ui->pushButton_deleteSemester->setEnabled(false);
    ui->pushButton_addTypeOfExam->setEnabled(false);
    ui->pushButton_editTypeOfExam->setEnabled(false);
    ui->pushButton_deleteTypeOfExam->setEnabled(false);

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
        updataData_nation();
        updataData_province();
        updataData_political();
        updataData_city();
        updataData_university();
        updataData_college();
        updataData_profession();
        updataData_status();
        updataData_socialStatus();
        updataData_blood();
        updataData_eye();
        updataData_skin();
        updataData_subject();
        updataData_year();
        updataData_semester();
        updataData_typeOfExam();
    }

    if(write=="Yes")
    {
        ui->pushButton_addNation->setEnabled(true);
        ui->pushButton_addPolitical->setEnabled(true);
        ui->pushButton_addProvince->setEnabled(true);
        ui->pushButton_addCity->setEnabled(true);
        ui->pushButton_addUniversity->setEnabled(true);
        ui->pushButton_addCollege->setEnabled(true);
        ui->pushButton_addProfession->setEnabled(true);
        ui->pushButton_addStatus->setEnabled(true);
        ui->pushButton_addSocialStatus->setEnabled(true);
        ui->pushButton_addBlood->setEnabled(true);
        ui->pushButton_addEye->setEnabled(true);
        ui->pushButton_addSkin->setEnabled(true);
        ui->pushButton_addSubject->setEnabled(true);
        ui->pushButton_addYear->setEnabled(true);
        ui->pushButton_addSemester->setEnabled(true);
        ui->pushButton_addTypeOfExam->setEnabled(true);
        connect(ui->pushButton_addNation,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addNation);
        connect(ui->pushButton_editNation,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editNation);
        connect(ui->pushButton_deleteNation,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteNation);
        connect(ui->listWidget_nation,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editNation->setEnabled(true);
        });
        connect(ui->listWidget_nation,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteNation->setEnabled(true);
        });

        connect(ui->pushButton_addPolitical,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addPolitical);
        connect(ui->pushButton_editPolitical,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editPolitical);
        connect(ui->pushButton_deletePolitical,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deletePolitical);
        connect(ui->listWidget_political,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editPolitical->setEnabled(true);
        });
        connect(ui->listWidget_political,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deletePolitical->setEnabled(true);
        });

        connect(ui->pushButton_addProvince,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addProvince);
        connect(ui->pushButton_editProvince,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editProvince);
        connect(ui->pushButton_deleteProvince,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteProvince);
        connect(ui->listWidget_province,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editProvince->setEnabled(true);
        });
        connect(ui->listWidget_province,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteProvince->setEnabled(true);
        });

        connect(ui->pushButton_addCity,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addCity);
        connect(ui->pushButton_editCity,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editCity);
        connect(ui->pushButton_deleteCity,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteCity);
        connect(ui->listWidget_city,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editCity->setEnabled(true);
        });
        connect(ui->listWidget_city,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteCity->setEnabled(true);
        });

        connect(ui->pushButton_addUniversity,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addUniversity);
        connect(ui->pushButton_editUniversity,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editUniversity);
        connect(ui->pushButton_deleteUniversity,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteUniversity);
        connect(ui->listWidget_university,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editUniversity->setEnabled(true);
        });
        connect(ui->listWidget_university,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteUniversity->setEnabled(true);
        });

        connect(ui->pushButton_addCollege,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addCollege);
        connect(ui->pushButton_editCollege,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editCollege);
        connect(ui->pushButton_deleteCollege,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteCollege);
        connect(ui->listWidget_college,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editCollege->setEnabled(true);
        });
        connect(ui->listWidget_college,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteCollege->setEnabled(true);
        });

        connect(ui->pushButton_addProfession,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addProfession);
        connect(ui->pushButton_editProfession,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editProfession);
        connect(ui->pushButton_deleteProfession,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteProfession);
        connect(ui->listWidget_profession,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editProfession->setEnabled(true);
        });
        connect(ui->listWidget_profession,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteProfession->setEnabled(true);
        });

        connect(ui->pushButton_addStatus,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addStatus);
        connect(ui->pushButton_editStatus,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editStatus);
        connect(ui->pushButton_deleteStatus,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteStatus);
        connect(ui->listWidget_status,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editStatus->setEnabled(true);
        });
        connect(ui->listWidget_status,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteStatus->setEnabled(true);
        });

        connect(ui->pushButton_addSocialStatus,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addSocialStatus);
        connect(ui->pushButton_editSocialStatus,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editSocialStatus);
        connect(ui->pushButton_deleteSocialStatus,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteSocialStatus);
        connect(ui->listWidget_socialStatus,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editSocialStatus->setEnabled(true);
        });
        connect(ui->listWidget_socialStatus,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteSocialStatus->setEnabled(true);
        });

        connect(ui->pushButton_addBlood,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addBlood);
        connect(ui->pushButton_editBlood,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editBlood);
        connect(ui->pushButton_deleteBlood,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteBlood);
        connect(ui->listWidget_blood,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editBlood->setEnabled(true);
        });
        connect(ui->listWidget_blood,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteBlood->setEnabled(true);
        });

        connect(ui->pushButton_addEye,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addEye);
        connect(ui->pushButton_editEye,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editEye);
        connect(ui->pushButton_deleteEye,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteEye);
        connect(ui->listWidget_eye,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editEye->setEnabled(true);
        });
        connect(ui->listWidget_eye,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteEye->setEnabled(true);
        });

        connect(ui->pushButton_addSkin,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addSkin);
        connect(ui->pushButton_editSkin,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editSkin);
        connect(ui->pushButton_deleteSkin,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteSkin);
        connect(ui->listWidget_skin,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editSkin->setEnabled(true);
        });
        connect(ui->listWidget_skin,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteSkin->setEnabled(true);
        });

        connect(ui->pushButton_addSubject,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addSubject);
        connect(ui->pushButton_editSubject,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editSubject);
        connect(ui->pushButton_deleteSubject,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteSubject);
        connect(ui->listWidget_subject,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editSubject->setEnabled(true);
        });
        connect(ui->listWidget_subject,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteSubject->setEnabled(true);
        });

        connect(ui->pushButton_addYear,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addYear);
        connect(ui->pushButton_editYear,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editYear);
        connect(ui->pushButton_deleteYear,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteYear);
        connect(ui->listWidget_year,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editYear->setEnabled(true);
        });
        connect(ui->listWidget_year,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteYear->setEnabled(true);
        });

        connect(ui->pushButton_addSemester,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addSemester);
        connect(ui->pushButton_editSemester,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editSemester);
        connect(ui->pushButton_deleteSemester,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteSemester);
        connect(ui->listWidget_semester,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editSemester->setEnabled(true);
        });
        connect(ui->listWidget_semester,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteSemester->setEnabled(true);
        });

        connect(ui->pushButton_addTypeOfExam,&QPushButton::clicked,this,&DataDictionary::clickPushButton_addTypeOfExam);
        connect(ui->pushButton_editTypeOfExam,&QPushButton::clicked,this,&DataDictionary::clickPushButton_editTypeOfExam);
        connect(ui->pushButton_deleteTypeOfExam,&QPushButton::clicked,this,&DataDictionary::clickPushButton_deleteTypeOfExam);
        connect(ui->listWidget_typeOfExam,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_editTypeOfExam->setEnabled(true);
        });
        connect(ui->listWidget_typeOfExam,&QListWidget::itemSelectionChanged,this,[this](){
            ui->pushButton_deleteTypeOfExam->setEnabled(true);
        });
    }
}

DataDictionary::~DataDictionary()
{
    delete ui;
}

void DataDictionary::updataData_nation()
{
    ui->listWidget_nation->clear();
    if(query->exec("select name from nation"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_nation->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_political()
{
    ui->listWidget_political->clear();
    if(query->exec("select name from political"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_political->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_province()
{
    ui->listWidget_province->clear();
    if(query->exec("select name from province"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_province->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_city()
{
    ui->listWidget_city->clear();
    if(query->exec("select name from city"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_city->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_university()
{
    ui->listWidget_university->clear();
    if(query->exec("select name from university"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_university->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_college()
{
    ui->listWidget_college->clear();
    if(query->exec("select name from college"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_college->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_profession()
{
    ui->listWidget_profession->clear();
    if(query->exec("select name from profession"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_profession->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_status()
{
    ui->listWidget_status->clear();
    if(query->exec("select name from status"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_status->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_socialStatus()
{
    ui->listWidget_socialStatus->clear();
    if(query->exec("select name from socialstatus"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_socialStatus->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_blood()
{
    ui->listWidget_blood->clear();
    if(query->exec("select name from blood"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_blood->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_eye()
{
    ui->listWidget_eye->clear();
    if(query->exec("select name from eye"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_eye->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_skin()
{
    ui->listWidget_skin->clear();
    if(query->exec("select name from skin"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_skin->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_subject()
{
    ui->listWidget_subject->clear();
    if(query->exec("select name from subject"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_subject->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_year()
{
    ui->listWidget_year->clear();
    if(query->exec("select name from year"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_year->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_semester()
{
    ui->listWidget_semester->clear();
    if(query->exec("select name from semester"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_semester->addItem(name);
            }
        }
    }
}

void DataDictionary::updataData_typeOfExam()
{
    ui->listWidget_typeOfExam->clear();
    if(query->exec("select name from typeofexam"))
    {
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->listWidget_typeOfExam->addItem(name);
            }
        }
    }
}

void DataDictionary::clickPushButton_addNation()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加民族"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {

        if(query->exec(QString("INSERT INTO `nation` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加民族成功。");
        }
        updataData_nation();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editNation()
{
    bool ok;
    QString oldname=ui->listWidget_nation->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑民族"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_nation->currentItem()->setText(text);
        if(query->exec(QString("UPDATE nation set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改民族成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteNation()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_nation->currentItem();
        ui->listWidget_nation->removeItemWidget(ui->listWidget_nation->currentItem());
        if(query->exec(QString("DELETE FROM `nation` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除民族成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addPolitical()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加政治面貌"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `political` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加政治面貌成功。");
        }
        updataData_political();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editPolitical()
{
    bool ok;
    QString oldname=ui->listWidget_political->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑政治面貌"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_political->currentItem()->setText(text);
        if(query->exec(QString("UPDATE political set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改政治面貌成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deletePolitical()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_political->currentItem();
        ui->listWidget_political->removeItemWidget(ui->listWidget_political->currentItem());
        if(query->exec(QString("DELETE FROM `political` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除政治面貌成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addProvince()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加省份"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `province` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加省份成功。");
        }
        updataData_province();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editProvince()
{
    bool ok;
    QString oldname=ui->listWidget_province->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑省份"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_province->currentItem()->setText(text);
        if(query->exec(QString("UPDATE province set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改省份成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteProvince()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_province->currentItem();
        ui->listWidget_province->removeItemWidget(ui->listWidget_province->currentItem());
        if(query->exec(QString("DELETE FROM `province` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除省份成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addCity()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加城市"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `city` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加城市成功。");
        }
        updataData_city();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editCity()
{
    bool ok;
    QString oldname=ui->listWidget_city->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑城市"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_city->currentItem()->setText(text);
        if(query->exec(QString("UPDATE city set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改城市成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteCity()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_city->currentItem();
        ui->listWidget_city->removeItemWidget(ui->listWidget_city->currentItem());
        if(query->exec(QString("DELETE FROM `city` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除省份成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addUniversity()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加大学"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `university` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加大学成功。");
        }
        updataData_university();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editUniversity()
{
    bool ok;
    QString oldname=ui->listWidget_university->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑大学"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_university->currentItem()->setText(text);
        if(query->exec(QString("UPDATE university set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改大学成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteUniversity()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_university->currentItem();
        ui->listWidget_university->removeItemWidget(ui->listWidget_university->currentItem());
        if(query->exec(QString("DELETE FROM `university` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除大学成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addCollege()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加学院"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `college` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加学院成功。");
        }
        updataData_college();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editCollege()
{
    bool ok;
    QString oldname=ui->listWidget_college->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑学院"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_college->currentItem()->setText(text);
        if(query->exec(QString("UPDATE college set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改学院成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteCollege()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_college->currentItem();
        ui->listWidget_college->removeItemWidget(ui->listWidget_college->currentItem());
        if(query->exec(QString("DELETE FROM `college` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除学院成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addProfession()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加专业"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `profession` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加专业成功。");
        }
        updataData_profession();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editProfession()
{
    bool ok;
    QString oldname=ui->listWidget_profession->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑专业"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_profession->currentItem()->setText(text);
        if(query->exec(QString("UPDATE profession set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改专业成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteProfession()
{
    QMessageBox message(QMessageBox::NoIcon,  "提示",  "确定删除该条数据吗?", QMessageBox::Yes | QMessageBox::No, NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_profession->currentItem();
        ui->listWidget_profession->removeItemWidget(ui->listWidget_profession->currentItem());
        if(query->exec(QString("DELETE FROM `profession` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除专业成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addStatus()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加状态"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `status` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加状态成功。");
        }
        updataData_status();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editStatus()
{
    bool ok;
    QString oldname=ui->listWidget_status->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑状态"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_status->currentItem()->setText(text);
        if(query->exec(QString("UPDATE status set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改状态成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteStatus()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_status->currentItem();
        ui->listWidget_status->removeItemWidget(ui->listWidget_status->currentItem());
        if(query->exec(QString("DELETE FROM `status` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除状态成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addSocialStatus()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加社交途径"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `socialstatus` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加社交途径成功。");
        }
        updataData_socialStatus();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editSocialStatus()
{
    bool ok;
    QString oldname=ui->listWidget_socialStatus->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑社交途径"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_socialStatus->currentItem()->setText(text);
        if(query->exec(QString("UPDATE socialstatus set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改社交途径成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteSocialStatus()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_socialStatus->currentItem();
        ui->listWidget_socialStatus->removeItemWidget(ui->listWidget_socialStatus->currentItem());
        if(query->exec(QString("DELETE FROM `socialstatus` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除社交途径成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addBlood()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加血型"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `blood` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加血型成功。");
        }
        updataData_blood();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editBlood()
{
    bool ok;
    QString oldname=ui->listWidget_blood->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑血型"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_blood->currentItem()->setText(text);
        if(query->exec(QString("UPDATE blood set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改血型成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteBlood()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_blood->currentItem();
        ui->listWidget_blood->removeItemWidget(ui->listWidget_blood->currentItem());
        if(query->exec(QString("DELETE FROM `blood` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除血型成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addEye()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加瞳色"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `eye` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加瞳色成功。");
        }
        updataData_eye();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editEye()
{
    bool ok;
    QString oldname=ui->listWidget_eye->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑瞳色"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_eye->currentItem()->setText(text);
        if(query->exec(QString("UPDATE eye set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改瞳色成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteEye()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_eye->currentItem();
        ui->listWidget_eye->removeItemWidget(ui->listWidget_eye->currentItem());
        if(query->exec(QString("DELETE FROM `eye` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除瞳色成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addSkin()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加肤色"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `skin` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加肤色成功。");
        }
        updataData_skin();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editSkin()
{
    bool ok;
    QString oldname=ui->listWidget_skin->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑肤色"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_skin->currentItem()->setText(text);
        if(query->exec(QString("UPDATE eye set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改肤色成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteSkin()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_skin->currentItem();
        ui->listWidget_skin->removeItemWidget(ui->listWidget_skin->currentItem());
        if(query->exec(QString("DELETE FROM `skin` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除肤色成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addSubject()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加科目"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `subject` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加科目成功。");
        }
        updataData_subject();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editSubject()
{
    bool ok;
    QString oldname=ui->listWidget_subject->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑科目"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_subject->currentItem()->setText(text);
        if(query->exec(QString("UPDATE subject set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改科目成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteSubject()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_subject->currentItem();
        ui->listWidget_subject->removeItemWidget(ui->listWidget_subject->currentItem());
        if(query->exec(QString("DELETE FROM `subject` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除科目成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addYear()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加年份"),tr("年份:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `year` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加年份成功。");
        }
        updataData_year();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editYear()
{
    bool ok;
    QString oldname=ui->listWidget_year->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑年份"),tr("名称:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_year->currentItem()->setText(text);
        if(query->exec(QString("UPDATE year set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改年份成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteYear()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_year->currentItem();
        ui->listWidget_year->removeItemWidget(ui->listWidget_year->currentItem());
        if(query->exec(QString("DELETE FROM `year` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除年份成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addSemester()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加学期"),tr("学期:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `semester` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加学期成功。");
        }
        updataData_semester();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editSemester()
{
    bool ok;
    QString oldname=ui->listWidget_semester->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑学期"),tr("学期:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_semester->currentItem()->setText(text);
        if(query->exec(QString("UPDATE semester set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改学期成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteSemester()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_semester->currentItem();
        ui->listWidget_semester->removeItemWidget(ui->listWidget_semester->currentItem());
        if(query->exec(QString("DELETE FROM `semester` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除学期成功。");
            delete item;
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_addTypeOfExam()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("添加考试类型"),tr("类型:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        if(query->exec(QString("INSERT INTO `typeofexam` (`name`) VALUES ('%1')").arg(text)))
        {
            qDebug()<<tr("DataDictionary：添加考试类型成功。");
        }
        updataData_typeOfExam();
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_editTypeOfExam()
{
    bool ok;
    QString oldname=ui->listWidget_semester->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("编辑考试类型"),tr("类型:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        ui->listWidget_semester->currentItem()->setText(text);
        if(query->exec(QString("UPDATE typeofexam set name = '%1' WHERE name = '%2'").arg(text,oldname)))
        {
            qDebug()<<tr("DataDictionary：修改考试类型成功。");
        }
        emit needUpdataData();
    }
}

void DataDictionary::clickPushButton_deleteTypeOfExam()
{
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        QListWidgetItem *item=ui->listWidget_typeOfExam->currentItem();
        ui->listWidget_typeOfExam->removeItemWidget(ui->listWidget_typeOfExam->currentItem());
        if(query->exec(QString("DELETE FROM `typeofexam` WHERE name = '%1'").arg(item->text())))
        {
            qDebug()<<tr("DataDictionary：删除考试类型成功。");
            delete item;
        }
        emit needUpdataData();
    }
}





