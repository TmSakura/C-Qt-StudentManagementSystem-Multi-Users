#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username,QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow),username(username)
{
    ui->setupUi(this);

    db = QSqlDatabase::database("conn");
    query=new QSqlQuery(db);

    ui->label_welcome->setText(QString("欢迎您，"+username));

    ui->pushButton_add->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_editOrView->setEnabled(false);
    ui->pushButton_export->setEnabled(false);
    ui->pushButton_import->setEnabled(false);
    ui->pushButton_user->setEnabled(false);
    ui->pushButton_search->setEnabled(false);
    ui->pushButton_search_2->setEnabled(false);
    ui->pushButton_dataDictionary->setEnabled(false);

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
        //Tab1
        ui->pushButton_user->setEnabled(true);
        ui->pushButton_search->setEnabled(true);
        ui->pushButton_dataDictionary->setEnabled(true);
        ui->pushButton_export->setEnabled(true);
        ui->pushButton_user->setEnabled(true);
        updataData_table();
        updataDataDictonary();
        ui->tableWidget_info->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->checkBox_dataOfAdmission->setChecked(true);
        ui->dateEdit_dataOfAdmission->setEnabled(false);
        connect(ui->pushButton_dataDictionary,&QPushButton::clicked,this,&MainWindow::clickPushButton_dataDictionary);
        connect(ui->pushButton_editOrView,&QPushButton::clicked,this,&MainWindow::clickPushBUtton_editView);
        connect(ui->pushButton_export,&QPushButton::clicked,this,&MainWindow::clickPushButton_exportExcel);
        connect(ui->pushButton_user,&QPushButton::clicked,this,&MainWindow::clickPushButton_user);
        connect(ui->pushButton_search,&QPushButton::clicked,this,&MainWindow::clickPushButton_search);
        connect(ui->checkBox_dataOfAdmission,&QCheckBox::stateChanged,this,[this](){
            if(ui->checkBox_dataOfAdmission->isChecked())
                ui->dateEdit_dataOfAdmission->setEnabled(false);
            else
                ui->dateEdit_dataOfAdmission->setEnabled(true);
        });
        connect(ui->pushButton_clean,&QPushButton::clicked,this,&MainWindow::updataDataDictonary);
        connect(ui->tableWidget_info,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_editOrView->setEnabled(true);
        });

        //Tab2
        ui->pushButton_search_2->setEnabled(true);
        updataData_table_2();
        updataDataDictonary_2();
        ui->tableWidget_info_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->checkBox_dataOfAdmission_2->setChecked(true);
        ui->dateEdit_dataOfAdmission_2->setEnabled(false);
        ui->checkBox_dataOfGraduation->setChecked(true);
        ui->dateEdit_dataOfGraduation->setEnabled(false);
        connect(ui->pushButton_search_2,&QPushButton::clicked,this,&MainWindow::clickPushButton_search_2);
        connect(ui->checkBox_dataOfAdmission_2,&QCheckBox::stateChanged,this,[this](){
            if(ui->checkBox_dataOfAdmission_2->isChecked())
                ui->dateEdit_dataOfAdmission_2->setEnabled(false);
            else
                ui->dateEdit_dataOfAdmission_2->setEnabled(true);
        });
        connect(ui->checkBox_dataOfGraduation,&QCheckBox::stateChanged,this,[this](){
            if(ui->checkBox_dataOfGraduation->isChecked())
                ui->dateEdit_dataOfGraduation->setEnabled(false);
            else
                ui->dateEdit_dataOfGraduation->setEnabled(true);
        });

        //Tab3
        updataDataChart();

        //connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,&MainWindow::updataDataChart);
    }

    if(remove=="Yes")
    {
        //Tab1
        ui->pushButton_add->setEnabled(true);
        connect(ui->pushButton_add,&QPushButton::clicked,this,&MainWindow::clickPushButton_add);
        connect(ui->pushButton_delete,&QPushButton::clicked,this,&MainWindow::clickPushBUtton_delete);
        connect(ui->tableWidget_info,&QTableWidget::itemClicked,this,[this](){
            ui->pushButton_delete->setEnabled(true);
        });
    }
    if(print=="Yes")
    {
        ui->pushButton_print->setEnabled(true);
    }
    if(import=="Yes")
    {
        ui->pushButton_import->setEnabled(true);
        connect(ui->pushButton_import,&QPushButton::clicked,this,&MainWindow::clickPushButton_importExcel);
    }
    if(admin=="Yes")
    {

    }

    connect(ui->pushButton_exit,&QPushButton::clicked,this,[this](){
        parentWidget()->show();
        emit exitReturnLogin();
        delete this;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updataData_table()
{

    ui->tableWidget_info->clear();
    ui->tableWidget_info->setColumnCount(8);
    ui->tableWidget_info->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"学号"<<"性别"<<"入学日期"<<"专业"<<"城市"<<"政治面貌"<<"状态");

    if(query->exec(QString("SELECT studentinfo.name,studentinfo.number,studentinfo.sex,studentinfo.dataOfAdmission,"
                           "studentinfo.profession,studentinfo.city,studentinfo.political,studentinfo.status FROM studentinfo")))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_info->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_info->setItem(count,0,new QTableWidgetItem(query->value(0).toString()));
                ui->tableWidget_info->setItem(count,1,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_info->setItem(count,2,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_info->setItem(count,3,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_info->setItem(count,4,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_info->setItem(count,5,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget_info->setItem(count,6,new QTableWidgetItem(query->value(6).toString()));
                ui->tableWidget_info->setItem(count,7,new QTableWidgetItem(query->value(7).toString()));
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

void MainWindow::updataDataDictonary()
{
    ui->lineEdit_name->setText("");
    ui->lineEdit_number->setText("");
    ui->comboBox_sex->setCurrentIndex(-1);

    if(query->exec("select name from province"))
    {
        ui->comboBox_province->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_province->addItem(name);
            }
        }
        ui->comboBox_province->setCurrentIndex(-1);
    }
    if(query->exec("select name from profession"))
    {
        ui->comboBox_profession->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_profession->addItem(name);
            }
        }
        ui->comboBox_profession->setCurrentIndex(-1);
    }
    if(query->exec("select name from city"))
    {
        ui->comboBox_city->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_city->addItem(name);
            }
        }
        ui->comboBox_city->setCurrentIndex(-1);
    }
    if(query->exec("select name from university"))
    {
        ui->comboBox_university->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_university->addItem(name);
            }
        }
        ui->comboBox_university->setCurrentIndex(-1);
    }
    if(query->exec("select name from status"))
    {
        ui->comboBox_status->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_status->addItem(name);
            }
        }
        ui->comboBox_status->setCurrentIndex(-1);
    }
}

void MainWindow::clickPushButton_add()
{
    StudentInfo *studentinfo = new StudentInfo(username,this);
    hide();
    studentinfo->show();
    studentinfo->setAttribute(Qt::WA_QuitOnClose,false);    //解决关闭主窗口后子窗口依旧还在的问题
    studentinfo->setAttribute(Qt::WA_DeleteOnClose);        //解决关闭窗口后内存未释放问题
    connect(studentinfo,&StudentInfo::needUpdataData,this,[this](){
        updataData_table();
        updataData_table_2();
        updataDataDictonary();
        updataDataDictonary_2();
    });
}

void MainWindow::clickPushBUtton_editView()
{
    QList<QTableWidgetItem*> items = ui->tableWidget_info->selectedItems();
    QTableWidgetItem *item = items.at(1);
    QString text = item->text();
    StudentInfo *studentinfo = new StudentInfo(username,this,1,text);
    hide();
    studentinfo->show();
    studentinfo->setAttribute(Qt::WA_QuitOnClose,false);
    studentinfo->setAttribute(Qt::WA_DeleteOnClose);
    connect(studentinfo,&StudentInfo::needUpdataData,this,&MainWindow::updataData_table);
    connect(studentinfo,&StudentInfo::needUpdataData,this,&MainWindow::updataData_table_2);
}

void MainWindow::clickPushBUtton_delete()
{
    QList<QTableWidgetItem*> items = ui->tableWidget_info->selectedItems();
    QTableWidgetItem *item = items.at(1);
    QString text = item->text();
    QMessageBox message(QMessageBox::NoIcon,"提示","确定删除该条数据吗?",QMessageBox::Yes|QMessageBox::No,NULL);
    message.setAttribute(Qt::WA_QuitOnClose,false);
    if(message.exec() == QMessageBox::Yes)
    {
        query->exec(QString("DELETE FROM `studentinfo` WHERE number = '%1'").arg(text));
        query->exec(QString("DELETE FROM `honor` WHERE number = '%1'").arg(text));
        query->exec(QString("DELETE FROM `scholarship` WHERE number = '%1'").arg(text));
        query->exec(QString("DELETE FROM `debt` WHERE number = '%1'").arg(text));
        query->exec(QString("DELETE FROM `punish` WHERE number = '%1'").arg(text));
        query->exec(QString("DELETE FROM `grade` WHERE number = '%1'").arg(text));
        query->exec(QString("DELETE FROM `file` WHERE number = '%1'").arg(text));

        updataData_table();
        updataData_table_2();
    }
}

void MainWindow::clickPushButton_dataDictionary()
{
    DataDictionary *datadictionary = new DataDictionary(username,this);
    datadictionary->show();
    datadictionary->setAttribute(Qt::WA_QuitOnClose,false);
    datadictionary->setAttribute(Qt::WA_DeleteOnClose);
    connect(datadictionary,&DataDictionary::needUpdataData,this,&MainWindow::updataDataDictonary);
    connect(datadictionary,&DataDictionary::needUpdataData,this,&MainWindow::updataDataDictonary_2);
}

void MainWindow::clickPushButton_user()
{
    UserControl *user=new UserControl(username,this);
    user->show();
    user->setAttribute(Qt::WA_QuitOnClose,false);
    user->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::clickPushButton_search()
{
    QString str="SELECT studentinfo.name,studentinfo.number,studentinfo.sex,studentinfo.dataOfAdmission,"
                "studentinfo.profession,studentinfo.city,studentinfo.political,"
                "studentinfo.status FROM studentinfo WHERE";
    if(ui->lineEdit_name->text()!="")
    {
        str+=QString(" name = '%1' AND").arg(ui->lineEdit_name->text());
    }
    if(ui->dateEdit_dataOfAdmission->text()!=""&&ui->dateEdit_dataOfAdmission->isEnabled())
    {
        str+=QString(" dataOfAdmission = '%1' AND").arg(ui->dateEdit_dataOfAdmission->text());
    }
    if(ui->comboBox_province->currentText()!="")
    {
        str+=QString(" province = '%1' AND").arg(ui->comboBox_province->currentText());
    }
    if(ui->lineEdit_number->text()!="")
    {
        str+=QString(" number = '%1' AND").arg(ui->lineEdit_number->text());
    }
    if(ui->comboBox_profession->currentText()!="")
    {
        str+=QString(" profession = '%1' AND").arg(ui->comboBox_profession->currentText());
    }
    if(ui->comboBox_city->currentText()!="")
    {
        str+=QString(" city = '%1' AND").arg(ui->comboBox_city->currentText());
    }
    if(ui->comboBox_university->currentText()!="")
    {
        str+=QString(" university = '%1' AND").arg(ui->comboBox_university->currentText());
    }
    if(ui->comboBox_status->currentText()!="")
    {
        str+=QString(" status = '%1' AND").arg(ui->comboBox_status->currentText());
    }

    if(str.at(str.size()-1)=="D")
        str.remove(str.size()-4,4);
    else/* if(str.at(str.size()-1)==" ")*/
    {
        str.remove(str.size()-6,6);
    }

    if(query->exec(str) && query->last())
    {
        ui->tableWidget_info->clear();
        ui->tableWidget_info->setColumnCount(8);
        ui->tableWidget_info->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"学号"<<"性别"<<"入学日期"<<"专业"<<"城市"<<"政治面貌"<<"状态");
        query->last();
        int num=query->at()+1;
        ui->tableWidget_info->setRowCount(num);

        query->first();
        int count = 0;
        while(true)        //挨个遍历数据
        {
            ui->tableWidget_info->setItem(count,0,new QTableWidgetItem(query->value(0).toString()));
            ui->tableWidget_info->setItem(count,1,new QTableWidgetItem(query->value(1).toString()));
            ui->tableWidget_info->setItem(count,2,new QTableWidgetItem(query->value(2).toString()));
            ui->tableWidget_info->setItem(count,3,new QTableWidgetItem(query->value(3).toString()));
            ui->tableWidget_info->setItem(count,4,new QTableWidgetItem(query->value(4).toString()));
            ui->tableWidget_info->setItem(count,5,new QTableWidgetItem(query->value(5).toString()));
            ui->tableWidget_info->setItem(count,6,new QTableWidgetItem(query->value(6).toString()));
            ui->tableWidget_info->setItem(count,7,new QTableWidgetItem(query->value(7).toString()));

            count++;
            if(!query->next())
            {
                break;
            }
        }
    }
    else
    {
        ui->tableWidget_info->clearContents();
        ui->tableWidget_info->setRowCount(0);
    }

}

void MainWindow::clickPushButton_importExcel()
{

    QString strFilePathName = QFileDialog::getOpenFileName(this,QStringLiteral("选择Excel文件"),"",tr("Exel file(*.xls *.xlsx)"));
    if(strFilePathName.isNull())
    {
        return ;
    }

    QAxObject *excel = new QAxObject(this);     //连接Excel控件
    if (excel->setControl("Excel.Application"))
    {

    }
    else
    {
        excel->setControl("ket.Application");   //连接Excel控件
    }
    excel->setProperty("Visible", false);       //不显示窗体
    QAxObject* workbooks = excel->querySubObject("WorkBooks");          //获取工作簿集合
    workbooks->dynamicCall("Open(const QString&)", strFilePathName);    //打开已存在的工作簿
    QAxObject* workbook = excel->querySubObject("ActiveWorkBook");      //获取当前工作簿
    //QAxObject* sheets = workbook->querySubObject("Sheets");             //获取工作表集合，Sheets也可换用WorkSheets
    QAxObject* sheet = workbook->querySubObject("WorkSheets(int)", 1);  //获取工作表集合的工作表1，即sheet1
    QAxObject* range = sheet->querySubObject("UsedRange");              //获取该sheet的使用范围对象
    QVariant var = range->dynamicCall("Value");
    delete range;
    QVariantList varRows = var.toList();        //得到表格中的所有数据
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    for(int i = 0; i < rowCount; ++i)
    {
        QVariantList rowData = varRows[i].toList();
        query->exec(QString("SELECT * FROM studentinfo WHERE number = '%1'").arg(rowData[1].toString()));
        if(query->last())
        {
            QMessageBox::information(this,"提示","有学号重复，跳过该条数据");
            continue;
        }
        query->clear();
        query->exec(QString("INSERT INTO studentinfo (`name`,`number`,`sex`,`nation`,`political`,`birthData`,`birthPlace`,`idCard`,"
                            "`province`,`city`,`university`, `college`, `profession`, `status`, `dataOfAdmission`, `dataOfGraduation`,"
                            "`homeAddress`,`phone`,`socialStatus`,`blood`,`eye`,`skin`,`fatherName`,`fatherWork`,`motherName`,`motherWork`,"
                            "`parentOtherInformation`,`photo`,`otherInterest`) VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10',"
                            "'%11','%12','%13','%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26','%27','%28',"
                            "'%29')").arg(rowData[0].toString(),rowData[1].toString(),rowData[2].toString(),
                rowData[3].toString(),rowData[4].toString(),rowData[5].toString(),
                rowData[6].toString(),rowData[7].toString(),rowData[8].toString(),
                rowData[9].toString(),rowData[10].toString(),rowData[11].toString(),
                rowData[12].toString(),rowData[13].toString(),rowData[14].toString(),
                rowData[15].toString(),rowData[16].toString(),rowData[17].toString(),
                rowData[18].toString(),rowData[19].toString(),rowData[20].toString(),
                rowData[21].toString(),rowData[22].toString(),rowData[23].toString(),
                rowData[24].toString(),rowData[25].toString(),rowData[26].toString(),
                rowData[27].toString(),rowData[28].toString()));
    }

    excel->dynamicCall("Quit(void)");
    delete excel;
    updataData_table();
    updataData_table_2();
}

void MainWindow::clickPushButton_exportExcel()
{

}

void MainWindow::updataData_table_2()
{
    ui->tableWidget_info_2->clear();
    ui->tableWidget_info_2->setColumnCount(8);
    ui->tableWidget_info_2->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"肤色"<<"瞳色"<<"血型"<<"社交途径"<<"入学时间"<<"毕业时间");

    if(query->exec(QString("SELECT studentinfo.name,studentinfo.sex,studentinfo.skin,studentinfo.eye,"
                           "studentinfo.blood,studentinfo.socialStatus,studentinfo.dataOfAdmission,studentinfo.dataOfGraduation FROM studentinfo")))
    {
        if(query->last()!= 0)
        {
            query->last();
            int num=query->at()+1;
            ui->tableWidget_info_2->setRowCount(num);

            query->first();
            int count = 0;
            while(true)        //挨个遍历数据
            {
                ui->tableWidget_info_2->setItem(count,0,new QTableWidgetItem(query->value(0).toString()));
                ui->tableWidget_info_2->setItem(count,1,new QTableWidgetItem(query->value(1).toString()));
                ui->tableWidget_info_2->setItem(count,2,new QTableWidgetItem(query->value(2).toString()));
                ui->tableWidget_info_2->setItem(count,3,new QTableWidgetItem(query->value(3).toString()));
                ui->tableWidget_info_2->setItem(count,4,new QTableWidgetItem(query->value(4).toString()));
                ui->tableWidget_info_2->setItem(count,5,new QTableWidgetItem(query->value(5).toString()));
                ui->tableWidget_info_2->setItem(count,6,new QTableWidgetItem(query->value(6).toString()));
                ui->tableWidget_info_2->setItem(count,7,new QTableWidgetItem(query->value(7).toString()));
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

void MainWindow::updataDataDictonary_2()
{
    ui->lineEdit_name_2->setText("");

    if(query->exec("select name from skin"))
    {
        ui->comboBox_skin->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_skin->addItem(name);
            }
        }
        ui->comboBox_skin->setCurrentIndex(-1);
    }
    if(query->exec("select name from eye"))
    {
        ui->comboBox_eye->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_eye->addItem(name);
            }
        }
        ui->comboBox_eye->setCurrentIndex(-1);
    }
    if(query->exec("select name from blood"))
    {
        ui->comboBox_blood->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_blood->addItem(name);
            }
        }
        ui->comboBox_blood->setCurrentIndex(-1);
    }
    if(query->exec("select name from socialstatus"))
    {
        ui->comboBox_socialStatus->clear();
        while (query->next())
        {
            QString name = query->value("name").toString();
            if(!name.isEmpty())
            {
                ui->comboBox_socialStatus->addItem(name);
            }
        }
        ui->comboBox_socialStatus->setCurrentIndex(-1);
    }
}

void MainWindow::updataDataChart()
{
    //绘制饼图
    QPieSeries *series = new QPieSeries();
    //添加饼图切片的标签和值
    QList<QString>listName;
    QSqlQuery *query1=new QSqlQuery(db);
    QSqlQuery *query2=new QSqlQuery(db);
    query1->exec("SELECT name FROM province");
    int count=0;
    int maxnum=0,max_index=0;
    float totalValue=0;
    while (query1->next())
    {
        QString name = query1->value("name").toString();
        query2->exec(QString("SELECT * FROM studentinfo WHERE province = '%1'").arg(name));
        query2->last();
        int num=query2->at()+1;
        if(!name.isEmpty())
        {
            if(maxnum<num)
            {
                maxnum=num;
                max_index=count;
            }
            series->append(name,num);
            totalValue += num;
            count++;
        }
    }
    series->setHoleSize(0.0);//孔大小0.0-1.0
    series->setHorizontalPosition(0.5);//水平位置，默认0.5，0.0-1.0
    series->setLabelsPosition(QPieSlice::LabelOutside);
    series->setLabelsVisible(true);
    series->setPieSize(0.7);//饼图尺寸，默认0.7
    series->setPieStartAngle(0);//0度为12点钟方向
    series->setVerticalPosition(0.5);
    series->setVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("学生地区分布图");
    chart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
    chart->setAnimationOptions(QChart::AllAnimations);//设置启用或禁用动画
    chart->setLocalizeNumbers(true);//数字是否本地化
    chart->setTitleBrush(QBrush(QColor(255,255,255)));//设置标题Brush
    chart->setTitleFont(QFont("微软雅黑",20));//设置标题字体
    chart->legend()->setAlignment(Qt::AlignLeft);//对齐
    chart->legend()->setLabelColor(QColor(255,128,255));//设置标签颜色
    chart->legend()->setVisible(true);//设置是否可视
    chart->legend()->setBorderColor(QColor(255,255,170,185));//设置边框颜色
    QFont font = chart->legend()->font();
    font.setItalic(!font.italic());
    chart->legend()->setFont(font);//设置字体为斜体
    font.setPointSizeF(12);
    chart->legend()->setFont(font);//设置字体大小
    chart->legend()->setFont(QFont("微软雅黑"));//设置字体类型

    //操作单个切片
    srand(time(NULL));
    for(int i=0;i<count;i++)
    {
        QColor qc = QColor::fromHsl(rand()%360,rand()%256,rand()%200);
        QPieSlice *slice = series->slices().at(i);
        //slice->setExploded();//切片是否与饼图分离
        slice->setLabelVisible(true);
        slice->setLabelColor(QColor(qc.red(),qc.green(),qc.blue()));
        slice->setColor(QColor(qc.red(),qc.green(),qc.blue()));
        slice->setLabel(slice->label()+"-"+QString("%1").arg(slice->value())+"-"+QString("%1").arg(slice->value()/totalValue*100)+"%");
        slice->setLabelFont(QFont("微软雅黑"));
        slice->setLabelVisible(true);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QFrame *frame=new QFrame();
    QHBoxLayout *layout=new QHBoxLayout(frame);
    layout->addWidget(chartView);
    frame->show();

    QHBoxLayout *layout2=new QHBoxLayout(ui->tab_3);
    layout2->addWidget(frame);
}

void MainWindow::clickPushButton_search_2()
{
    QString str="SELECT studentinfo.name,studentinfo.sex,studentinfo.skin,studentinfo.eye,"
                "studentinfo.blood,studentinfo.socialStatus,studentinfo.dataOfAdmission,"
                "studentinfo.dataOfGraduation FROM studentinfo WHERE";
    if(ui->lineEdit_name_2->text()!="")
    {
        str+=QString(" name = '%1' AND").arg(ui->lineEdit_name_2->text());
    }
    if(ui->comboBox_sex->currentText()!="")
    {
        str+=QString(" sex = '%1' AND").arg(ui->comboBox_sex->currentText());
    }
    if(ui->comboBox_skin->currentText()!="")
    {
        str+=QString(" skin = '%1' AND").arg(ui->comboBox_skin->currentText());
    }
    if(ui->comboBox_eye->currentText()!="")
    {
        str+=QString(" eye = '%1' AND").arg(ui->comboBox_eye->currentText());
    }
    if(ui->comboBox_blood->currentText()!="")
    {
        str+=QString(" blood = '%1' AND").arg(ui->comboBox_blood->currentText());
    }
    if(ui->comboBox_socialStatus->currentText()!="")
    {
        str+=QString(" socialStatus = '%1' AND").arg(ui->comboBox_socialStatus->currentText());
    }
    if(ui->dateEdit_dataOfAdmission_2->text()!=""&&ui->dateEdit_dataOfAdmission_2->isEnabled())
    {
        str+=QString(" dataOfAdmission = '%1' AND").arg(ui->dateEdit_dataOfAdmission_2->text());
    }
    if(ui->dateEdit_dataOfGraduation->text()!=""&&ui->dateEdit_dataOfGraduation->isEnabled())
    {
        str+=QString(" dataOfGraduation = '%1' AND").arg(ui->dateEdit_dataOfGraduation->text());
    }

    if(str.at(str.size()-1)=="D")
        str.remove(str.size()-4,4);
    else/* if(str.at(str.size()-1)==" ")*/
    {
        str.remove(str.size()-6,6);
    }
    if(query->exec(str) && query->last())
    {
        ui->tableWidget_info_2->clear();
        ui->tableWidget_info_2->setColumnCount(8);
        ui->tableWidget_info_2->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"肤色"<<"瞳色"<<"血型"<<"社交途径"<<"入学时间"<<"毕业时间");
        query->last();
        int num=query->at()+1;
        ui->tableWidget_info_2->setRowCount(num);

        query->first();
        int count = 0;
        while(true)        //挨个遍历数据
        {
            ui->tableWidget_info_2->setItem(count,0,new QTableWidgetItem(query->value(0).toString()));
            ui->tableWidget_info_2->setItem(count,1,new QTableWidgetItem(query->value(1).toString()));
            ui->tableWidget_info_2->setItem(count,2,new QTableWidgetItem(query->value(2).toString()));
            ui->tableWidget_info_2->setItem(count,3,new QTableWidgetItem(query->value(3).toString()));
            ui->tableWidget_info_2->setItem(count,4,new QTableWidgetItem(query->value(4).toString()));
            ui->tableWidget_info_2->setItem(count,5,new QTableWidgetItem(query->value(5).toString()));
            ui->tableWidget_info_2->setItem(count,6,new QTableWidgetItem(query->value(6).toString()));
            ui->tableWidget_info_2->setItem(count,7,new QTableWidgetItem(query->value(7).toString()));

            count++;
            if(!query->next())
            {
                break;
            }
        }
    }
    else
    {
        ui->tableWidget_info_2->clearContents();
        ui->tableWidget_info_2->setRowCount(0);
    }
}


