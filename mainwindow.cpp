#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerevent.h"
#include <QIcon>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QLabel>


VirtualKeyboard* MainWindow::virtualKeyboard =NULL;
InputEditKeyEventFilter* MainWindow::EditKeyEventFilter=NULL;
SystemConfigEventFilter* MainWindow::systemConfigEventFilter = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAutoFillBackground(true);
    currentMainWindowShowType = MASTERPREVIEW;
    listVideoW.clear();

    createSingletonKeyBorad();
    createSingletonEventFilter();

    // createDialog_timeZoneSetting();
    //createDialog_passwordSetting();
    //createDialog_welcome();
    createVideoWindow(1);

    //createDialog_config();
    //createReplayWindow();
}

void MainWindow::createSingletonKeyBorad()
{
    if(virtualKeyboard == NULL)
        virtualKeyboard = new VirtualKeyboard(this);
}

void MainWindow::createSingletonEventFilter()
{
    if(EditKeyEventFilter == NULL)
        EditKeyEventFilter = new InputEditKeyEventFilter(this);
    if(systemConfigEventFilter == NULL)
        systemConfigEventFilter = new SystemConfigEventFilter(this);
}


bool MainWindow::event(QEvent *event)
{


    return QWidget::event(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createReplayWindow()
{
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();

    if(replayWindow == NULL){
        replayWindow = new ReplayWindow(this);
        replayWindow->setGeometry(0,0,deskRect.width(),deskRect.height());
        replayWindow->init();

        connect(replayWindow,SIGNAL(signal_switchWindow(WindowType)),this,SLOT(slot_switchWindow(WindowType)));

    }
    replayWindow->show();
}

void MainWindow::createDialog_config()
{
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();

    if(nvrConfig == NULL){
        nvrConfig = new NvrConfig(this);
        nvrConfig->setGeometry((deskRect.width()-nvrConfig->width())/2,(deskRect.height()-nvrConfig->height())/2,nvrConfig->width(),nvrConfig->height());


        connect(nvrConfig,SIGNAL(signal_switchWindow(WindowType )),this,SLOT(slot_switchWindow(WindowType )));

    }
    nvrConfig->show();
}

void MainWindow::createVideoWindow(int n)
{

    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();

    int widthPerRect = (screenRect.width() - rectSpace *(videoN-1))/videoN;
    int heightPerRect = (screenRect.height() - rectSpace *(videoN-1))/videoN;
    for (int i=0;i<videoN;i++) {

        for(int j=0;j<videoN;j++){//横向添加
            VideoWindow *videoWindow = new VideoWindow(this,widthPerRect,heightPerRect,i*videoN+j);
            videoWindow->setParent(this);
            connect(videoWindow,SIGNAL(signal_selectVideo(int)),this,SLOT(slot_selectVideo(int)));
            connect(videoWindow,SIGNAL(signal_dClickVideo(int,bool)),this,SLOT(slot_dClickVideo(int,bool)));

            connect(videoWindow,SIGNAL(signal_masterControl(int,MasterControl)),this,SLOT(slot_masterControl(int,MasterControl)));
            videoWindow->setGeometry((widthPerRect+rectSpace)*j ,(heightPerRect+rectSpace)*i,widthPerRect,heightPerRect);



            listVideoW.append(videoWindow);
        }
    }
}
void MainWindow::createDialog_timeZoneSetting()
{
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();


    if(timeZoneSetting == NULL){
        timeZoneSetting = new Timezonesetting(this);

        timeZoneSetting->setDefaultTimeZone(3);
        connect(timeZoneSetting,SIGNAL(signal_timezoneStr(QString)),this,SLOT(slot_timezoneStr(QString)));
        timeZoneSetting->setGeometry((deskRect.width()-timeZoneSetting->width())/2,(deskRect.height()-timeZoneSetting->height())/2,timeZoneSetting->width(),timeZoneSetting->height());
        timeZoneSetting->show();
    }
}

void MainWindow::createDialog_passwordSetting()
{
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();

    if(passwordSetting == NULL){
        passwordSetting = new PasswordSetting(this);
        connect(passwordSetting,SIGNAL(signal_password(QString,QString)),this,SLOT(slot_passwordSetting(QString,QString)));
        passwordSetting->setGeometry((deskRect.width()-passwordSetting->width())/2,(deskRect.height()-passwordSetting->height())/2,passwordSetting->width(),passwordSetting->height());
        passwordSetting->show();
    }
}

void MainWindow::createDialog_welcome()
{
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();

    if(welcome == NULL){
        welcome = new Welcome(this);
        connect(welcome,SIGNAL(signal_loginStr(QString)),this,SLOT(slot_loginStr(QString)));
        welcome->setGeometry((deskRect.width()-welcome->width())/2,(deskRect.height()-welcome->height())/2,welcome->width(),welcome->height());
        welcome->show();
    }
}


void MainWindow::paintEvent(QPaintEvent*)
{
    //    QPainter pt(this);

    //    QColor c(Qt::gray);
    //    c.setAlpha(0);
    //    pt.fillRect(rect(), c);
    //    QPen pen(QColor("#252525"),rectSpace);

    //    pen.setBrush(QBrush(QColor("#252525")));
    //    pt.setPen(pen);


    //  int widthPerRect = (rect().width() - rectSpace *(videoN-1))/videoN;
    //   int heightPerRect = (rect().height() - rectSpace *(videoN-1))/videoN;

    //    for(int i = 0;i<videoN-1;i++){//画线
    //        pt.drawLine(widthPerRect*(i+1) + rectSpace*i,0,widthPerRect*(i+1) + rectSpace*i,rect().height());//竖线
    //        pt.drawLine(0,heightPerRect*(i+1) + rectSpace*i,rect().width(),heightPerRect*(i+1) + rectSpace*i);//横线
    //    }
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
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
#include <QLabel>
void MainWindow::popMenu()
{


    //初始化菜单
    if(rightMouseMenu == NULL){
        rightMouseMenu = new QMenu(this);

        rightMouseMenu->setStyleSheet("background-color: #171717;padding:0px;border:none;");
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

        QWidgetAction *buttonActionSpace2 = new QWidgetAction(this);
        QLabel *lable2 = new QLabel(this);
        lable2 ->setFixedSize(QSize(210,10));
        lable2->setStyleSheet("background-color: #171717;");
        buttonActionSpace2->setDefaultWidget(lable2);

        QWidgetAction *buttonActionSpace3 = new QWidgetAction(this);
        QLabel *lable3 = new QLabel(this);
        lable3 ->setFixedSize(QSize(210,10));
        lable3->setStyleSheet("background-color: #171717;");
        buttonActionSpace3->setDefaultWidget(lable3);

        QWidgetAction *buttonActionSpace4 = new QWidgetAction(this);
        QLabel *lable4 = new QLabel(this);
        lable4 ->setFixedSize(QSize(210,10));
        lable4->setStyleSheet("background-color: #171717;");
        buttonActionSpace4->setDefaultWidget(lable4);

        QWidgetAction *buttonActionCloudControl = new QWidgetAction(this);
        QWidgetAction *buttonActionReplay = new QWidgetAction(this);
        QWidgetAction *buttonActionDeviceSet = new QWidgetAction(this);
        QWidgetAction *buttonActionSystemSet = new QWidgetAction(this);

        QPushButton *pbtnCloudControl =  createSelfBtn(tr("PTZ Control"),":/images/menu_cloudcontrol.png");
        buttonActionCloudControl->setDefaultWidget(pbtnCloudControl);

        QPushButton *pbtnReplay =  createSelfBtn(tr("Video Replay"),":/images/menu_replay.png");
        buttonActionReplay->setDefaultWidget(pbtnReplay);

        QPushButton *pbtnDeviceSet =  createSelfBtn(tr("Device Setting"),":/images/menu_deviceManager.png");
        buttonActionDeviceSet->setDefaultWidget(pbtnDeviceSet);

        QPushButton *pbtnSystemSet =  createSelfBtn(tr("System Setting"),":/images/menu_systemmanager.png");
        buttonActionSystemSet->setDefaultWidget(pbtnSystemSet);

        //动作添加到菜单

        rightMouseMenu->addAction(buttonActionSpace);
        rightMouseMenu->addAction(buttonActionCloudControl);
        rightMouseMenu->addAction(buttonActionSpace1);
        rightMouseMenu->addAction(buttonActionReplay);
        rightMouseMenu->addAction(buttonActionSpace2);
        rightMouseMenu->addAction(buttonActionDeviceSet);
        rightMouseMenu->addAction(buttonActionSpace3);
        rightMouseMenu->addAction(buttonActionSystemSet);
        rightMouseMenu->addAction(buttonActionSpace4);

        //给动作设置信号槽
        connect( pbtnCloudControl, SIGNAL(clicked()),this,SLOT(slot_menuSelectCloudControl()));
        connect( pbtnReplay, SIGNAL(clicked()),this,SLOT(slot_menuSelectReplay()));
        connect( pbtnDeviceSet, SIGNAL(clicked()),this,SLOT(slot_menuSelectDeviceSet()));
        connect( pbtnSystemSet,SIGNAL(clicked()), this,SLOT(slot_menuSelectSystemSet()));
    }

    rightMouseMenu->exec(QCursor::pos());
}

void MainWindow::slot_menuSelectCloudControl()
{
    rightMouseMenu->close();

}

void MainWindow::slot_menuSelectReplay()
{

    slot_switchWindow(REPLAYVIDEO);
    rightMouseMenu->close();
}
void MainWindow::slot_menuSelectDeviceSet()
{

    slot_switchWindow(DEVICESET);
    rightMouseMenu->close();
}
void MainWindow::slot_menuSelectSystemSet()
{
    slot_switchWindow(SYSTEMSET);
    rightMouseMenu->close();
}

void MainWindow::showMasterVideo(bool isShow)
{
    if(listVideoW.size()<=0)
        createVideoWindow(4);

    if(isShow){

        for (int i=0;i<listVideoW.size();i++)
            listVideoW.at(i)->show();

    }else {

        for (int i=0;i<listVideoW.size();i++)
            listVideoW.at(i)->hide();
    }

}
void MainWindow::slot_switchWindow(WindowType type)
{


    //显示切换的窗口
    qDebug()<<" WindowType  "<<type;

    switch (type) {
    case MASTERPREVIEW:
        if(currentMainWindowShowType == REPLAYVIDEO){
            replayWindow->hide();
            showMasterVideo(true);
        }
        currentMainWindowShowType = type;
        if(nvrConfig!=NULL && nvrConfig->isVisible())
            nvrConfig->hide();
        break;
    case REPLAYVIDEO:
        if(currentMainWindowShowType == MASTERPREVIEW){
            showMasterVideo(false);
            createReplayWindow();
        }

        currentMainWindowShowType = type;
        if(nvrConfig!=NULL && nvrConfig->isVisible())
            nvrConfig->hide();
        break;
    case SYSTEMSET:
        if(nvrConfig == NULL)
            createDialog_config();

        nvrConfig->showSystemSet();

        break;
    case DEVICESET:

        if(nvrConfig == NULL)
            createDialog_config();

        nvrConfig->showDeviceSet();
        break;

    default:
        return;
    }
}

QPushButton *MainWindow::createSelfBtn(QString btnTxt,QString res)
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
    btn->setLayout(myLayout);
    return btn;
}


void MainWindow::slot_dClickVideo(int identify,bool isMax)
{
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();
    int widthPerRect = (screenRect.width() - rectSpace *(videoN-1))/videoN;
    int heightPerRect = (screenRect.height() - rectSpace *(videoN-1))/videoN;
    for (int i=0;i<listVideoW.size();i++) {

        VideoWindow *w = listVideoW.at(i);
        if(identify == w->getIdentify()){


            if(w->isMax){

                // w->setVisible(true);
                int hi = i/2;
                int vi = i%2;



                w->setGeometry((widthPerRect+rectSpace)*vi,(heightPerRect+rectSpace)*hi,widthPerRect,heightPerRect);
                w->adjustWsize(widthPerRect,heightPerRect);
                w->isMax = false;
            }else {


                w->setGeometry(0,0,screenRect.width(),screenRect.height());
                w->adjustWsize(screenRect.width(),screenRect.height());
                w->isMax = true;




            }

        }else{



            if(!isMax)
                w->hide();
            else
                w->show();


        }
    }
}

void MainWindow::slot_selectVideo(int identify)
{

    for (int i=0;i<listVideoW.size();i++) {

        VideoWindow *w = listVideoW.at(i);
        if(identify == w->getIdentify()){
            if(!w->isSelect){
                w->showControl();
                w->isSelect = true;
            }

        }

        else{
            if(w->isSelect){
                w->hideControl();
                w->isSelect = false;
            }

        }
    }
}

void MainWindow::slot_masterControl(int identify,MasterControl type)
{


}

void MainWindow::slot_passwordSetting(QString password,QString confirm)
{

}

void MainWindow::slot_timezoneStr(QString timezone)
{

}

void MainWindow::slot_loginStr(QString pwd)
{

}
