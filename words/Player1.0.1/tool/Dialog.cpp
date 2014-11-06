#include "Dialog.h"
#include "../base/BaseSetting.h"

Dialog::Dialog(QWidget *parent)
{

    arcR=10;
    isLeftPressDown=false;
    moveTimes=0;
    this->dir=NONE;
    this->setMouseTracking(true);

    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(BaseSetting::getbackGroundImage());
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);


   // setAttribute(Qt::WA_TranslucentBackground, true);
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                       | Qt::WindowMaximizeButtonHint);
}
void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    pen.setColor(QColor(245,245,246,100));
    pen.setWidth(8);
    p.setPen(pen);
    p.drawRoundedRect(0, 0, width() - 1, height() - 1, 20, 20);

     round_rect();
}



//根据鼠标位置，判断是否需要改变鼠标图标
    void Dialog::region(const QPoint &cursorGlobalPoint)
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

    void Dialog::mousePressEvent(QMouseEvent *event)
    {

        if(event->button()==Qt::LeftButton)
        {
            isLeftPressDown=true;
            event->accept();
        }
    }


    ///鼠标松开
    void Dialog::mouseReleaseEvent(QMouseEvent *event)
    {
        if(event->button()==Qt::LeftButton)
        {
            isLeftPressDown=false;
            if(dir!=NONE)
            {
                this->releaseMouse();
                this->setCursor(QCursor(Qt::ArrowCursor));
            }
            if(moveTimes>0)
            {
                moveTimes=0;
                this->setGeometry(QRect(frameWidget->x(),frameWidget->y(),frameWidget->width(),frameWidget->height()));
                this->resize(frameWidget->width(),frameWidget->height());
                delete frameWidget;
            }
        }
    }

    ////鼠标移动时进行的操作，包括拖放
    void Dialog::mouseMoveEvent(QMouseEvent *event)
    {

        QPoint gloPoint=event->globalPos();
        if(!isLeftPressDown)
        {
            this->region(gloPoint);
            if(event->button()!=Qt::LeftButton)
            {
                    this->region(gloPoint);
            }
        }
        else
        {
            if(++moveTimes==1)
            {
                dragPosition=event->globalPos()-this->frameGeometry().topLeft();

                frameWidget=new FrameWidget(this);
                frameWidget->setGeometry(QRect(this->x(),this->y(),this->width(),this->height()));
                frameWidget->show();

            }
            QRect rect=frameWidget->rect();//
            QPoint tl=frameWidget->mapToGlobal(rect.topLeft());
            QPoint rb=frameWidget->mapToGlobal(rect.bottomRight());
            if(dir!=NONE)
            {
                QRect rMove(tl,rb);
                switch(dir)
                {
                case    LEFT:
                    if(rb.x()-gloPoint.x()<=this->minimumWidth())
                    {
                        rMove.moveLeft(tl.x());
                    }
                    else
                    {
                        rMove.setX(gloPoint.x());
                    }
                    break;
                case RIGHT:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    break;
                case UP:
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case DOWN:
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case LEFTTOP:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;

                case RIGHTTOP:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case LEFTBOTTOM:
                    rMove.setHeight(gloPoint.y() - tl.y());
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    break;
                case RIGHTBOTTOM:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                default:
                    break;
                }
               frameWidget->setGeometry(rMove.x(),rMove.y(),rMove.width(),rMove.height());
            }
            else
            {
                frameWidget->move(event->globalPos()-dragPosition);
                event->accept();
            }
        }

    //    PlayerWidget::mouseMoveEvent(event);
    }


    void Dialog::resizeEvent(QResizeEvent *event)
    {
        resize(this->width(),this->height());
        round_rect();
    }



    //圆角实现函数
    void Dialog::round_rect()
    {
    //    QBitmap bmp(this->size());
    //    bmp.fill(this,0,0);
    //    QPainter p(&bmp);
    //    p.setPen(Qt::NoPen);

    //    p.setBrush(Qt::black);     ////设置图片外窗体的背景

    //    p.setRenderHint(QPainter::Antialiasing);//Anti aliasing
    //    p.drawRoundedRect(bmp.rect(), 10, 10,Qt::AbsoluteSize); //Four
    //    setMask(bmp);


        QBitmap bmp(this->size());
        bmp.fill();
        QPainter p(&bmp);
    //    p.setPen(Qt::NoPen);
    //    p.setBrush(Qt::black);
        p.setRenderHint(QPainter::Antialiasing);
      //  p.drawRoundedRect(bmp.rect(), 20, 20); //四个角都是圆弧
        //只要上边角圆弧
        QPainterPath path;
       //逆时针
        path.moveTo(arcR, 0);
        path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
        path.lineTo(0, this->height()-arcR);
        path.arcTo(0, this->height()-arcR*2, arcR * 2, arcR * 2, 180.0f, 90.0f);
        path.lineTo(this->width()-arcR, this->height());
         path.arcTo(this->width()-arcR*2, this->height()-2*arcR, arcR * 2, arcR * 2, 270.0f, 90.0f);
        path.lineTo(this->width(), arcR);
        path.arcTo(this->width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
        path.lineTo(arcR, 0);
        p.drawPath(path);
        p.fillPath(path, QBrush(Qt::red)); //arm和windows平台没有这行代码将显示一个透明的空空的框
        setMask(bmp);
    }
