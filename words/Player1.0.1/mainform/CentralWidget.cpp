#include "CentralWidget.h"
#include "../base/BaseSetting.h"

CentralWidget::CentralWidget(QWidget *parent)
    :QWidget(parent)
{
    arcR=10;

    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(BaseSetting::getbackGroundImage());
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

}

void CentralWidget::resizeEvent(QResizeEvent *)
{
    round_rect();
}


//圆角实现函数
void CentralWidget::round_rect()
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
