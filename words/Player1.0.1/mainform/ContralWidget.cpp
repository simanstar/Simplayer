#include "ContralWidget.h"
ContralWidget::ContralWidget(QMainWindow *mainWindow,SimPlayer *player)
    :QWidget(mainWindow)
{
    isLeftPressDown=false;
    moveTimes=0;
    this->dir=NONE;
    this->player=player;
    this->mainWindow=mainWindow;
    timer=new QTimer(this);
    clickTimes=0;

    toolBar=new ToolBar(this);
    toolBar->setSimPlayer(player);
    titleBar=new TitleBar(mainWindow);
    control= new ControlPanel(player);
    seekbar=new SeekBar(control);
    playlist=new PlayList(this);




    QVBoxLayout *vbox=new QVBoxLayout;
    this->setLayout(vbox);
  //  vbox->addWidget(playlist);

    vbox->addWidget(toolBar);
    vbox->addWidget(titleBar);
    vbox->addWidget(playlist);
    vbox->addWidget(control);
    vbox->addWidget(seekbar);



    QVBoxLayout *vbox2=new QVBoxLayout;
   //  this->setLayout(vbox2);


    vbox2->addWidget(toolBar);
    vbox2->addWidget(titleBar);
    vbox2->addWidget(playlist);
    vbox2->addWidget(control);
    vbox2->addWidget(seekbar);





    this->setMouseTracking(true);

    connect(control->player,SIGNAL(UpdateTime()),seekbar,SIGNAL(UpdateTime()));


    connect(timer,SIGNAL(timeout()),this,SLOT(mouseClick()));
    connect(playlist,SIGNAL(mediaChanged(QString)),control,SLOT(change_media(QString)));
    connect(toolBar,SIGNAL(addNewFile(QStringList*)),playlist,SLOT(addFile(QStringList*)));

    //动画

    titlebar_slideout=new QPropertyAnimation(titleBar,"geometry");
    toolBar_slideout=new QPropertyAnimation(toolBar,"geometry");
    seekbar_slideout=new QPropertyAnimation(seekbar,"geometry");
    playlist_slideout=new QPropertyAnimation(playlist,"geometry");
    control_slideout=new QPropertyAnimation(control,"geometry");

    titlebar_slidein=new QPropertyAnimation(titleBar,"geometry");
    toolBar_slidein=new QPropertyAnimation(toolBar,"geometry");
    seekbar_slidein=new QPropertyAnimation(seekbar,"geometry");
    playlist_slidein=new QPropertyAnimation(playlist,"geometry");
    control_slidein=new QPropertyAnimation(control,"geometry");


    //style


    QFile file(":/qss/SeekBar.qss");
    file.open(QFile::ReadOnly);


    this->setStyleSheet(file.readAll());

}
ContralWidget::~ContralWidget()
{

}

void ContralWidget::setMainWindow(QMainWindow *mainWindow)
{
    this->mainWindow=mainWindow;
}



void ContralWidget::resizeEvent(QResizeEvent *event)
{


  toolBar->setGeometry(10,0,this->width()/4,50);
  titleBar->setGeometry(this->width()-100,0,100,50);
  control->setGeometry(this->width()/3,this->height()-100,this->width()/3,100);

  seekbar->setGeometry(0,this->height()-28,this->width(),50);
  playlist->setGeometry(this->width()-160,this->height()/8,160,this->height()/2);

}



//根据鼠标位置，判断是否需要改变鼠标图标
void ContralWidget::region(const QPoint &cursorGlobalPoint)
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


void ContralWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        isLeftPressDown=true;
        clickTimes++;
        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
      //  resize(360,360);
        mainWindow->setWindowState( Qt::WindowFullScreen);
    }
}


///鼠标松开
void ContralWidget::mouseReleaseEvent(QMouseEvent *event)
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
            clickTimes=0;
            mainWindow->setGeometry(QRect(frameWidget->x(),frameWidget->y(),frameWidget->width(),frameWidget->height()));
            mainWindow->resize(frameWidget->width(),frameWidget->height());
            delete frameWidget;
        }
        else if(clickTimes==1)
        {
            timer->start(200);
        }
    }
}

////鼠标移动时进行的操作，包括拖放
void ContralWidget::mouseMoveEvent(QMouseEvent *event)
{

    QPoint gloPoint=event->globalPos();
    if(!isLeftPressDown)
    {
        if(!mainWindow->isMaximized())
        {
            this->region(gloPoint);
        }
        if(15<event->x() &&event->x()<this->width()-15&&this->height()-100 < event->y() && event->y() < this->height())
            show_seekbar();
        else
            hide_seekbar();
        if(control->x() < event->x() && event->x()< control->x()+control->width() &&this->height()-100 < event->y() && event->y()<this->height())
            show_control();
        else
            hide_control();

        if(this->width()-100 < event->x() &&event->x() <this->width()-10 && 50 < event->y() && event->y() < 5*this->height()/8)
            show_playlist();
        else
            hide_playlist();
        if(10<event->x()&&event->x()<this->width()/4 && 5<event->y() &&event->y()<25)
            show_toolBar();
        else
            hide_toolBar();

        if(this->width()-100<event->x() &&event->x()<this->width()-20 && 10<event->y() && event->y()<25)
            show_titlebar();
        else
            hide_titlebar();
    }
    else
    {
//        if(mainWindow->isMaximized())
//        {
//            return;
//        }
        if(++moveTimes==1)
        {
            dragPosition=event->globalPos()-mainWindow->frameGeometry().topLeft();

            frameWidget=new FrameWidget(this);
            frameWidget->setGeometry(QRect(mainWindow->x(),mainWindow->y(),mainWindow->width(),mainWindow->height()));
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
            if(mainWindow->isMaximized())
            {
                return;
            }
            frameWidget->move(event->globalPos()-dragPosition);
            event->accept();
        }
    }

//    PlayerWidget::mouseMoveEvent(event);
}

void ContralWidget::mouseClick()
{
    control->stateChanging();
    clickTimes=0;
    timer->stop();
}

void ContralWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    clickTimes=0;
    timer->stop();
    titleBar->showMaxRestore();
}

void ContralWidget::show_seekbar()
{

   if(seekbar->y()>this->height())
    {
//   QPropertyAnimation *slideout=new QPropertyAnimation(seekbar,"geometry");

        seekbar_slideout->setDuration(250);
        seekbar_slideout->setStartValue(QRect(0,this->height(),this->width(),50));
        seekbar_slideout->setEndValue(QRect(0,this->height()-28,this->width(),50));
        seekbar_slideout->start();
    }
}

void ContralWidget::hide_seekbar()
{

   if(seekbar->y()<this->height())
    {
//   QPropertyAnimation *slidein=new QPropertyAnimation(seekbar,"geometry");

        seekbar_slidein->setDuration(250);
        seekbar_slidein->setStartValue(QRect(0,seekbar->y(),this->width(),50));
        seekbar_slidein->setEndValue(QRect(0,this->height()+28,this->width(),50));
        seekbar_slidein->start();


    }


}




void ContralWidget::show_control()
{

   if(control->y()>this->height())
    {
  // QPropertyAnimation *slideout=new QPropertyAnimation(control,"geometry");

        control_slideout->setDuration(250);
        control_slideout->setStartValue(QRect(this->width()/3,this->height(),this->width()/3,100));
        control_slideout->setEndValue(QRect(this->width()/3,this->height()-100,this->width()/3,100));
        control_slideout->start();


    }
}

void ContralWidget::hide_control()
{

    if(control->y()<this->height())
    {
 // QPropertyAnimation *slidein=new QPropertyAnimation(control,"geometry");

        control_slidein->setDuration(250);
        control_slidein->setStartValue(QRect(this->width()/3,control->y(),this->width()/3,100));
        control_slidein->setEndValue(QRect(this->width()/3,this->height()+1,this->width()/3,100));
        control_slidein->start();


    }
}





void ContralWidget::show_playlist()
{


        if(playlist->x()>this->width())
             {
           // QPropertyAnimation *slideout=new QPropertyAnimation(playlist,"geometry");

                 playlist_slideout->setDuration(250);
                 playlist_slideout->setStartValue(QRect(this->width(),this->height()/8,160,this->height()/2));
                 playlist_slideout->setEndValue(QRect(this->width()-160,this->height()/8,160,this->height()/2));
                 playlist_slideout->start();


             }

}

void ContralWidget::hide_playlist()
{

      if(playlist->x()<this->width())
      {
   //  QPropertyAnimation *slidein=new QPropertyAnimation(playlist,"geometry");

          playlist_slidein->setDuration(250);
          playlist_slidein->setStartValue(QRect(playlist->x(),this->height()/8,160,this->height()/2));
          playlist_slidein->setEndValue(QRect(this->width()+1,this->height()/8,160,this->height()/2));
          playlist_slidein->start();
      }
}


void ContralWidget::show_toolBar()
{
    toolBar_slidein->setDuration(250);
    toolBar_slidein->setStartValue(QRect(10,-50,this->width()/4,50));
    toolBar_slidein->setEndValue(QRect(10,0,this->width()/4,50));
    toolBar_slidein->start();
}

void ContralWidget::hide_toolBar()
{
    toolBar_slideout->setDuration(250);
    toolBar_slideout->setStartValue(QRect(toolBar->x(),toolBar->y(),this->width()/4,50));
    toolBar_slideout->setEndValue(QRect(toolBar->x(),-50,this->width()/4,50));
    toolBar_slideout->start();
}



void ContralWidget::show_titlebar()
{
    if(titleBar->y()<0)
    {

         titlebar_slidein->setDuration(250);
         titlebar_slidein->setStartValue(QRect(this->width()-100,-50,100,50));
         titlebar_slidein->setEndValue(QRect(this->width()-100,0,100,50));
         titlebar_slidein->start();

    }
}




void ContralWidget::hide_titlebar()
{
    if(titleBar->y()==0)
    {

         titlebar_slideout->setDuration(250);
         titlebar_slideout->setStartValue(QRect(this->width()-100,titleBar->y(),100,50));
         titlebar_slideout->setEndValue(QRect(this->width()-100,-50,100,50));
         titlebar_slideout->start();

    }
}


