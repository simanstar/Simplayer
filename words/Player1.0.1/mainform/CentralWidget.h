#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H
#include <QtWidgets>

class CentralWidget:public QWidget
{
public:
    CentralWidget(QWidget *parent=0);
protected:
    void resizeEvent(QResizeEvent *);
private:
    void round_rect();
    //圆角半径
    int arcR;
};
#endif // CENTRALWIDGET_H
