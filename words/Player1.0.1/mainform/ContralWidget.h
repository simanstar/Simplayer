#ifndef CONTRALWIDGET_H
#define CONTRALWIDGET_H


#include "../panel/ControlPanel.h"
#include "../panel/SeekBar.h"
#include "../playlist/PlayList.h"
#include "../tool/FrameWidget.h"
#include "../tool/ToolBar.h"
#include "../title/titlebar.h"
class QTimer;

class ContralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContralWidget(QMainWindow *mainWindow,SimPlayer *player);
    ~ContralWidget();
    void setMainWindow(QMainWindow *mainWindow);
    ControlPanel  *control ;




protected:
    void resizeEvent(QResizeEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    //出场
    void show_control();
    void show_seekbar();
    void show_playlist();
    void show_toolBar();
    void show_titlebar();

    //退场

    void hide_control();
    void hide_seekbar();
    void hide_playlist();
    void hide_toolBar();
    void hide_titlebar();

    //检测边界
    void region(const QPoint &cursorGlobalPoint);
    void round_rect();
private slots:
    void mouseClick();

private:
    //
    QTimer *timer;
    int clickTimes;
    //移动窗口边框
    QMainWindow *mainWindow;
    FrameWidget *frameWidget;
    Direction dir;
    bool isLeftPressDown;
    QPoint dragPosition;
    int moveTimes;


    //窗口元素
    ToolBar *toolBar;
    TitleBar *titleBar;
    SeekBar *seekbar;
    PlayList *playlist;
    SimPlayer *player;
    //动画
    QPropertyAnimation *titlebar_slideout;
    QPropertyAnimation *toolBar_slideout;
    QPropertyAnimation *seekbar_slideout;
    QPropertyAnimation *playlist_slideout;
    QPropertyAnimation *control_slideout;


    QPropertyAnimation *titlebar_slidein;
    QPropertyAnimation *toolBar_slidein;
    QPropertyAnimation *seekbar_slidein;
    QPropertyAnimation *playlist_slidein;
    QPropertyAnimation *control_slidein;

};



#endif // CONTRALWIDGET_H
