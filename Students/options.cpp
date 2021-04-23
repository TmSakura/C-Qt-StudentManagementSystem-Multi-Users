#include "options.h"
#include "ui_options.h"
#include <QDebug>

Options::Options(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->show();

    QDir *dirPath = new QDir(":/styles/qss");
    QList<QFileInfo>file(dirPath->entryInfoList());
    for (auto it = file.begin(); it != file.end(); it++)
    {
        ui->comboBox_theme->addItem(it->fileName().remove(it->fileName().size()-4,4));
    }

    connect(ui->listWidget,&QListWidget::itemPressed,this,&Options::stackedWidget_change);
    connect(ui->pushButton_return,&QPushButton::clicked,this,&Options::clickPushButton_return);
    connect(ui->pushButton_confirm,&QPushButton::clicked,this,&Options::clickPushButton_confirm);
}

Options::~Options()
{
    delete ui;
}

void Options::clickPushButton_return()
{
    parentWidget()->show();
    delete this;
}

void Options::clickPushButton_confirm()
{
    clickPushButton_apply();
    clickPushButton_return();
}

void Options::clickPushButton_apply()
{
    updatedata_appearance();
}

void Options::stackedWidget_change()
{
    switch (ui->listWidget->currentRow())
    {
    case 0:
        ui->stackedWidget->setCurrentWidget(ui->page_appearance);
        ;
    }

}

void Options::updatedata_appearance()
{
    QString theme(ui->comboBox_theme->currentText()+".qss");
    theme=":/styles/qss/"+theme;
    QFile file(theme);
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
}
