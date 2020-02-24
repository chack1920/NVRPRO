#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

#include "timezonesetting.h"
#include "passwordsetting.h"
#include "welcome.h"
#include "masterPreview/videowindow.h"
#include "nvrConfig/nvrconfig.h"
#include "videoReplay/replaywindow.h"

#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();


public slots:
    //void slot_switchWindow(WindowType type);
protected:
    void paintEvent(QPaintEvent*);


    void mousePressEvent(QMouseEvent *event);

    bool event(QEvent *event);


private:
    Ui::MainWindow *ui;

    void popMenu();

    void createDialog_timeZoneSetting();
    void createDialog_passwordSetting();
    void createDialog_welcome();
    void createVideoWindow(int n);
    void createDialog_config();
    void createReplayWindow();

    void showMasterVideo(bool isShow);
    void switchWindow(WindowType type);
//    void drawVideoRect(QPainter *paint,int nxn);
//    void drawCloudControl(QPainter *paint);

    QPushButton *createSelfBtn(QString str,QString res);

    int const rectSpace = 2;//分屏的时候，相邻矩形的边距
    int const videoN = 2;//几乘几的视频显示

    QMenu *rightMouseMenu = NULL;

    QList<VideoWindow*> listVideoW;
    ReplayWindow *replayWindow = NULL;
    NvrConfig *nvrConfig = NULL;
    Timezonesetting *timeZoneSetting = NULL;
    PasswordSetting *passwordSetting = NULL;
    Welcome *welcome = NULL;

    WindowType currentShowType;
};

#endif // MAINWINDOW_H
