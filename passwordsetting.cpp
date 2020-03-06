#include "passwordsetting.h"
#include "ui_passwordsetting.h"
#include "mainwindow.h"
#include "messagedialog.h"
PasswordSetting::PasswordSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordSetting)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    setControlPostion();
}

PasswordSetting::~PasswordSetting()
{
    delete ui;
}


void PasswordSetting::setControlPostion()
{
    int labelW = 210;
    int labelH = 30;
    int labelY = 40;

    int label_2W = 270;
    int label_2H = 24;
    int label_2Y = 80;

    int lineEdit_passwordW = 312;
    int lineEdit_passwordH = 46;
    int lineEdit_passwordY = 134;

    int lineEdit_confirmW = 312;
    int lineEdit_confirmH = 46;
    int lineEdit_confirmY = 210;

    int btnW = 312;
    int btnH = 48;
    int btnY = 284;

    int thisW = this->width();
    int thisH = this->height();

    ui->label->setGeometry((thisW - labelW)/2,labelY,labelW,labelH);
    ui->label_2->setGeometry(QRect((thisW - label_2W)/2,label_2Y,label_2W,label_2H));
    ui->label_3->setGeometry(ui->label_2->x() - 8,ui->label_2->y(),8,label_2H);

    ui->lineEdit_password->setPasswordInput(true);
    ui->lineEdit_confirm->setPasswordInput(true);
    ui->lineEdit_password->installEventFilter(MainWindow::EditKeyEventFilter);
    ui->lineEdit_confirm->installEventFilter(MainWindow::EditKeyEventFilter);

    ui->lineEdit_password->setGeometry((thisW - lineEdit_passwordW)/2,lineEdit_passwordY,lineEdit_passwordW,lineEdit_passwordH);
    ui->lineEdit_confirm->setGeometry((thisW - lineEdit_confirmW)/2,lineEdit_confirmY,lineEdit_confirmW,lineEdit_confirmH);

    ui->pushButton_next->setGeometry((thisW - btnW)/2,btnY,btnW,btnH);
}



void PasswordSetting::on_pushButton_next_clicked()
{

    QString pwd = ui->lineEdit_password->text();
    QString confirm = ui->lineEdit_confirm->text();


    MessageDialog *dialog = new MessageDialog(this,"test");
    dialog->showDialogOnBottom(ui->pushButton_next,20,1000);

    emit signal_password(pwd,confirm);

}
