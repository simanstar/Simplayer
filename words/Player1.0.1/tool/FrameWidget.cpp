#include "FrameWidget.h"


FrameWidget::FrameWidget(QWidget *parent)
{
    this->dir=NONE;
    this->setMouseTracking(true);


     setAttribute(Qt::WA_TranslucentBackground, true);
     setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                       | Qt::WindowMaximizeButtonHint);
//    QWidget *centralWidget=new QWidget;
//    setCentralWidget(centralWidget);

//    QWidget *drawWidget=new QWidget;
//    QStackedLayout *stack=new QStackedLayout;
//    stack->addWidget(drawWidget);
//    stack->setStackingMode(QStackedLayout::StackAll);
//    centralWidget->setLayout(stack);

//    QPainter painter(this);
//    QPen pen;
//    pen.setColor(QColor(255,0,0));  //设置画笔为红色
//    painter.setPen(pen);  //选择画笔
//    painter.drawLine(0,0,100,100); //用该红色画笔画一条线，起点(0,0)，终点(100,100)
//    painter.end();


}
void FrameWidget::paintEvent(QPaintEvent *event)
{
//    QPainter *painter=new QPainter(this);
//  //  painter.setRenderHint(QPainter::Antialiasing,true);
//    painter->setPen(QPen(Qt::black,15,Qt::SolidLine,Qt::RoundCap));
//    painter->setBrush(QBrush(Qt::green,Qt::SolidPattern));
//    painter->drawRect(0,0,1000,740);

    QPainter p(this);
    QPen pen;
    pen.setColor(QColor(245,245,246,100));
    pen.setWidth(8);
    p.setPen(pen);
    p.drawRoundedRect(0, 0, width() - 1, height() - 1, 20, 20);
}


//根据鼠标位置，判断是否需要改变鼠标图标
    void FrameWidget::region(const QPoint &cursorGlobalPoint)
    {
        // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
        QRect rect = this->rect();
        QPoint tl = mapToGlobal(rect.topLeft());
        QPoint rb = mapToGlobal(rect.bottomRight());

        int x = cursorGlobalPoint.x();
        int y = cursorGlobalPoint.y();

        if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
            // 左上角
            dir = LEFTTOP;
            this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
        } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
            // 右下角
            dir = RIGHTBOTTOM;
            this->setCursor(QCursor(Qt::SizeFDiagCursor));
        } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
            //左下角
            dir = LEFTBOTTOM;
            this->setCursor(QCursor(Qt::SizeBDiagCursor));
        } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
            // 右上角
            dir = RIGHTTOP;
            this->setCursor(QCursor(Qt::SizeBDiagCursor));
        } else if(x <= tl.x() + PADDING && x >= tl.x()) {
            // 左边
            dir = LEFT;
            this->setCursor(QCursor(Qt::SizeHorCursor));
        } else if( x <= rb.x() && x >= rb.x() - PADDING) {
            // 右边
            dir = RIGHT;
            this->setCursor(QCursor(Qt::SizeHorCursor));
        }else if(y >= tl.y() && y <= tl.y() + PADDING){
            // 上边
            dir = UP;
            this->setCursor(QCursor(Qt::SizeVerCursor));
        } else if(y <= rb.y() && y >= rb.y() - PADDING) {
            // 下边
            dir = DOWN;
            this->setCursor(QCursor(Qt::SizeVerCursor));
        }else {
            // 默认
            dir = NONE;
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }



    ////鼠标移动时进行的操作，包括拖放
    void FrameWidget::mouseMoveEvent(QMouseEvent *event)
    {
        QPoint gloPoint=event->globalPos();
            this->region(gloPoint);

    //    PlayerWidget::mouseMoveEvent(event);
    }
