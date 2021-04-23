#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDir>

namespace Ui {
class Options;
}

class Options : public QMainWindow
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

private slots:
    void clickPushButton_return();
    void clickPushButton_confirm();
    void clickPushButton_apply();
    void stackedWidget_change();

    void updatedata_appearance();

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
