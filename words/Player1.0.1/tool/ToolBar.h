#ifndef TOOLBAR_H
#define TOOLBAR_H
#include<QtWidgets>
#include "../playkernel/SimPlayer.h"
#include "screenshot.h"
#include "synchronizedialog.h"
#include "adjustdialog.h"
#include "aboutdialog.h"

class ToolBar:public QWidget
{
    Q_OBJECT
public:
    ToolBar(QWidget *parent=0);
    void setSimPlayer(SimPlayer *simPlayer);
signals:
    void addNewFile(QStringList *fileList);
private slots:
    void openFile();    //打开文件槽
    void aboutInfo();   //信息帮助槽
    void snapShot();    //截图槽
    void synchronizeVideo();
    void adjustSet();
    void rotate();
private:
    void createButtons();
private:
    QToolButton *openButton;
    QToolButton *snapShotButton;
    QToolButton *rotateButton;
    QToolButton *synchronizeButton;
    QToolButton *adjustButton;
    QToolButton *aboutButton;

    SimPlayer *simPlayer;
};

#endif // TOOLBAR_H














//#ifndef TOOLBAR_H
//#define TOOLBAR_H
//#include<QtWidgets>
//#include "../playkernel/SimPlayer.h"
//#include "screenshot.h"
//#include "synchronizedialog.h"
//#include "audiosetwidget.h"
//#include "videosetdialog.h"
//#include "aboutdialog.h"

//class ToolBar:public QWidget
//{
//    Q_OBJECT
//public:
//    ToolBar(QWidget *parent=0);
//    void setSimPlayer(SimPlayer *simPlayer);
//signals:
//    void addNewFile(QStringList *fileList);
//private slots:
//    void openFile();    //打开文件槽
//    void aboutInfo();   //信息帮助槽
//    void snapShot();    //截图槽
//    void synchronizeVideo();
//    void audioSet();
//    void videoSet();
//    void rotate();
//private:
//    void createButtons();
//private:
//    QToolButton *openButton;
//    QToolButton *snapShotButton;
//    QToolButton *rotateButton;
//    QToolButton *synchronizeButton;
//    QToolButton *channelSetButton;
//    QToolButton *videoSetButton;
//    QToolButton *aboutButton;

//    SimPlayer *simPlayer;
//};

//#endif // TOOLBAR_H
