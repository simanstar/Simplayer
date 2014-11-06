#ifndef DIALOG_H
#define DIALOG_H
#include <QtWidgets>
#include <QDialog>
#include "FrameWidget.h"


class Dialog: public QDialog
{
public:
    Dialog(QWidget *parent=0);
protected:
    void resizeEvent(QResizeEvent *event);
    void  paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    void region(const QPoint &cursorGlobalPoint);
    void round_rect();
private:
    Direction dir;  //窗口大小改变时，记录改变方向
    int arcR;
    bool isLeftPressDown;
    QPoint dragPosition;
    int moveTimes;

    FrameWidget *frameWidget;
};

#endif // MAINWINDOW_H
