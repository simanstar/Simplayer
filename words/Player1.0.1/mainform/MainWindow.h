#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "../playkernel/PlayLabel.h"
#include <QtWidgets>
#include "ContralWidget.h"
#include "CentralWidget.h"


class MainWindow : public QMainWindow
{
   // Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int setArcR(int value);
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
private:
    void round_rect();
    void drawWindowShadow(QPainter &p);
    void HideSDLWindow(void);//创建一个sdl显示的区域，并且把其与主窗口中的play_widget绑定
private:


    PlayLabel *play_label;
    CentralWidget *centralwidget;
    ContralWidget *contralwidget;
    SimPlayer *player;

    int arcR;





};



#endif // MAINWINDOW_H
