#include "replaywindow.h"
#include "ui_replaywindow.h"
#include <QMouseEvent>
#include <QDebug>
ReplayWindow::ReplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReplayWindow)
{
    ui->setupUi(this);
}

void ReplayWindow::init()
{
    createTimeLine();
}

void ReplayWindow::createTimeLine()
{
    if(replayTimeline == NULL){
        replayTimeline = new ReplayTimeline(this);
        replayTimeline->setGeometry(0,926,1920,154);
        replayTimeline->init();

        connect(replayTimeline,SIGNAL(signal_popDateDialog()),this,SLOT(slot_popDateDialog()));
    }
}

void ReplayWindow::slot_popDateDialog()
{
    if(myCalendar == NULL){
        myCalendar = new MyCalendar(this);
        myCalendar->setGeometry(227,612,280,314);
        connect(myCalendar,SIGNAL(dateUpdate(QDate)),this,SLOT(slot_dateUpdate(QDate)));
    }
    myCalendar->show();
}

void ReplayWindow::slot_dateUpdate(QDate date)
{
    if(replayTimeline != NULL){
        replayTimeline->setDate(date);
    }
}

void ReplayWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseButtonDblClick){
        qDebug()<<"ReplayWindow MouseButtonDblClick";

    }

    if(event->button() == Qt::LeftButton)
    {

    }
    // 如果是鼠标右键按下
    else if(event->button() == Qt::RightButton)
    {
        qDebug()<<"鼠标右键按下";
        popMenu();
    }
}



void ReplayWindow::popMenu()
{
    QWidgetAction *buttonActionSpace = new QWidgetAction(this);
    QLabel *lable = new QLabel(this);
    lable ->setFixedSize(QSize(210,10));
    lable->setStyleSheet("background-color: #171717;");
    buttonActionSpace->setDefaultWidget(lable);
    QWidgetAction *buttonActionSpace1 = new QWidgetAction(this);
    QLabel *lable1 = new QLabel(this);
    lable1 ->setFixedSize(QSize(210,10));
    lable1->setStyleSheet("background-color: #171717;");
    buttonActionSpace1->setDefaultWidget(lable1);

    QWidgetAction *buttonActionCloudControl = new QWidgetAction(this);
    QWidgetAction *buttonActionReplay = new QWidgetAction(this);
    QWidgetAction *buttonActionDeviceSet = new QWidgetAction(this);
    QWidgetAction *buttonActionSystemSet = new QWidgetAction(this);


    QPushButton *pbtnCloudControl =  createSelfBtn(tr("PTZ Control"),":/images/menu_cloudcontrol.png");
    buttonActionCloudControl->setDefaultWidget(pbtnCloudControl);

    QPushButton *pbtnMaster =  createSelfBtn(tr("Master Preview"),":/images/menu_replay.png");
    buttonActionReplay->setDefaultWidget(pbtnMaster);

    QPushButton *pbtnDeviceSet =  createSelfBtn(tr("Device Setting"),":/images/menu_deviceManager.png");
    buttonActionDeviceSet->setDefaultWidget(pbtnDeviceSet);

    QPushButton *pbtnSystemSet =  createSelfBtn(tr("System Setting"),":/images/menu_systemmanager.png");
    buttonActionSystemSet->setDefaultWidget(pbtnSystemSet);

    //初始化菜单
    if(buttonMenu == NULL){
        buttonMenu = new QMenu(this);
        buttonMenu->setStyleSheet("background-color: #171717;padding:0px;border:none;");
        buttonMenu->addAction(buttonActionSpace);
        buttonMenu->addAction(buttonActionReplay);
        buttonMenu->addAction(buttonActionDeviceSet);
        buttonMenu->addAction(buttonActionSystemSet);
        buttonMenu->addAction(buttonActionSpace1);


        //给动作设置信号槽
        connect( pbtnMaster, SIGNAL(clicked()),this,SLOT(slot_MasterClick()));
        connect( pbtnDeviceSet, SIGNAL(clicked()), this,SLOT(slot_DeviceSetClick()));
        connect( pbtnSystemSet, SIGNAL(clicked()),this,SLOT(slot_SystemSetClick()));
    }
    buttonMenu->exec(QCursor::pos());
}

void ReplayWindow::slot_MasterClick()
{

    emit signal_switchWindow(MASTERPREVIEW);
    buttonMenu->close();
}
void ReplayWindow::slot_DeviceSetClick()
{

    emit signal_switchWindow(DEVICESET);
    buttonMenu->close();
}

void ReplayWindow::slot_SystemSetClick()
{
    emit signal_switchWindow(SYSTEMSET);
    buttonMenu->close();
}

QPushButton *ReplayWindow::createSelfBtn(QString btnTxt,QString res)
{
    const QSize btnSize(210,42);
    QPushButton *btn = new QPushButton(this);

    btn ->setFixedSize(btnSize);
    btn ->setStyleSheet("QPushButton{background-color: #171717;color:#ffffff;border:none}"
                        "QPushButton:pressed{background-color: #476BFD;}");
    btn->setFocusPolicy(Qt::NoFocus);
    QLabel* label = new QLabel();
    QLabel* label2 = new QLabel();
    label2->setFixedSize(QSize(20,20));
    QString sty = "border-image:url("+res+");background-color: transparent;color:#ffffff;";
    label->setStyleSheet("background-color: transparent;font-size: 16px;color:#ffffff;");
    label2 ->setStyleSheet(sty);

    label->setText(btnTxt);
    QHBoxLayout* myLayout = new QHBoxLayout();
    myLayout->addSpacing(12);
    myLayout->addWidget(label2);
    myLayout->addSpacing(6);
    myLayout->addWidget(label);
    myLayout->addStretch();
    btn->setLayout(myLayout);

    return btn;
}

ReplayWindow::~ReplayWindow()
{
    delete ui;
}
