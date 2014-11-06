#include "MainWindow.h"
#include "sdl/SDL.h"
#include "../base/BaseSetting.h"

////public////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint)

{

//    this->setAutoFillBackground(true);
//    QPalette palette;
//    QPixmap pixmap(":/images/dialogbackground.jpg");
//    palette.setBrush(QPalette::Window, QBrush(pixmap));
//    this->setPalette(palette);
    this->setWindowIcon(QIcon(":./iamges/window.icon"));
    this->setAttribute(Qt::WA_TranslucentBackground);

    arcR=10;
    centralwidget=new CentralWidget(this);

     play_label=new PlayLabel(centralwidget);
     player = new SimPlayer;
     contralwidget=new ContralWidget(this,player);
//   contralwidget->setMainWindow(this);



     play_label->setPlayer(player);



     //////////////////////////////////////////////////布局
 //    this->setCentralWidget(centralwidget);
     QStackedLayout *stack =new  QStackedLayout;
     stack->setStackingMode(QStackedLayout::StackAll);


     stack->addWidget(play_label);
     stack->addWidget(contralwidget);
 //   play_label->show();
      centralwidget->setLayout(stack);


      this->setGeometry(100,100,760,460);
      BaseSetting::readSettings();

      centralwidget->setGeometry(0,0,this->width()-15,this->height()-15);



    HideSDLWindow(); //先设置好这个，再创建线程

    connect(player,SIGNAL(display()),play_label,SLOT(display()));

}

MainWindow::~MainWindow()
{

}
int MainWindow::setArcR(int value)
{
    this->arcR=value;
    return this->arcR;
}

////protected////
void MainWindow::resizeEvent(QResizeEvent *event)
{
    resize(this->width(),this->height());
    centralwidget->setGeometry(0,0,this->width()-15,this->height()-15);
    if(this->isMaximized())
    {
        centralwidget->setGeometry(0,0,this->width(),this->height());
    }
    round_rect();
}
void MainWindow::closeEvent(QCloseEvent *)
{
    BaseSetting::writeSettings();
}

void MainWindow::HideSDLWindow(void)
{

       QWidget *widget=new QWidget;
        char winID[32] = {0};
        sprintf(winID, "SDL_WINDOWID=0x%lx", (long unsigned int)widget->winId());
        SDL_putenv(winID);
        widget->hide();



}


//圆角实现函数
void MainWindow::round_rect()
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


void MainWindow::paintEvent(QPaintEvent *)
{
    //阴影效果
    QPainter p(this);

    if(this->width() > 45 && this->height() > 45)
        drawWindowShadow(p);

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::white);
    p.drawRoundedRect(QRect(18,18,this->width() - 36,this->height() - 36),2.0f,2.0f);

//    centralwidget->setGeometry(10,10,this->width()-20,this->height()-20);


//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(10, 10, this->width()-20, this->height()-20);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.fillPath(path, QBrush(Qt::white));

//    QColor color(0, 0, 0, 50);
//    for(int i=0; i<10; i++)
//    {
//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
//        color.setAlpha(150 - qSqrt(i)*50);
//        painter.setPen(color);
//        painter.drawPath(path);
//    }
}

void MainWindow::drawWindowShadow(QPainter &p)
{
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/resources/shadow_left.png"));
    pixmaps.append(QPixmap(":/resources/shadow_right.png"));
    pixmaps.append(QPixmap(":/resources/shadow_top.png"));
    pixmaps.append(QPixmap(":/resources/shadow_bottom.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner1.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner2.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner3.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner4.png"));

    p.drawPixmap(0,0,20,20,pixmaps[4]);
    p.drawPixmap(this->width() - 20,0,20,20,pixmaps[5]);
    p.drawPixmap(0,this->height() - 20,20,20,pixmaps[6]);
    p.drawPixmap(this->width() - 20,this->height() - 20,20,20,pixmaps[7]);

    p.drawPixmap(0,20,20,this->height() - 40,pixmaps[0].scaled(20,this->height() - 40));
    p.drawPixmap(this->width() - 20,20,20,this->height() - 40,pixmaps[1].scaled(20,this->height() - 40));
    p.drawPixmap(20,0,this->width() - 40,20,pixmaps[2].scaled(this->width() - 40,20));
    p.drawPixmap(20,this->height() - 20,this->width() - 40,20,pixmaps[3].scaled(this->width() - 40,20));
}
