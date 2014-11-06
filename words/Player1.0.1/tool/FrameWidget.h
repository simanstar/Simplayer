#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H
#include <QtWidgets>
#define PADDING 6

enum Direction
{
    UP=0,
    DOWN=1,
    LEFT,RIGHT,LEFTTOP,LEFTBOTTOM,RIGHTBOTTOM,RIGHTTOP,NONE
};
class QPoint;
class  QPainter;
class FrameWidget: public QWidget
{
public:
    FrameWidget(QWidget *parent=0);
protected:
    void  paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    void region(const QPoint &cursorGlobalPoint);
private:
    Direction dir;  //窗口大小改变时，记录改变方向

};

#endif // MAINWINDOW_H
