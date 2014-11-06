#include "SeekBar.h"




SeekBar::SeekBar(ControlPanel *parent):
    QWidget(parent)

{



    control_parent=parent;
    click_bar=new ClickBar(this);
    edit_current_time=new QLabel;
    edit_total_time=new QLabel;

    click_bar->setOrientation(Qt::Horizontal);

    QHBoxLayout *seekbar_layout=new QHBoxLayout;
    seekbar_layout->addWidget(edit_current_time);
    seekbar_layout->addWidget(click_bar);
    seekbar_layout->addWidget(edit_total_time);
    this->setLayout(seekbar_layout);






    click_bar->setRange(0,100);


    connect(click_bar,SIGNAL(sliderPressed()),this,SLOT(change_is_pressed()));
    connect(click_bar,SIGNAL(sliderReleased()),this,SLOT(change_is_pressed()));
    connect(click_bar,SIGNAL(sliderPressed()),this,SLOT(close_audio_for_slidermove()));
    connect(click_bar,SIGNAL(sliderReleased()),this,SLOT(close_audio_for_slidermove()));

   // connect(click_bar,SIGNAL(sliderMoved(int)),this,SLOT(set_value(int)));
    connect(click_bar,SIGNAL(sliderMoved(int)),this,SLOT(seek_only_pause(int)));

    connect(click_bar,SIGNAL(value_changed_by_click(int)),this,SLOT(seek(int)));


    connect(this,SIGNAL(UpdateTime()),this,SLOT(UpdateSkin()));
    is_pressed=0;


}


SeekBar::~SeekBar()
{

}

void SeekBar::set_value(int value)
{
    click_bar->setValue(value);
}
void SeekBar::seek(int value)
{  if( control_parent->curState==StartState||control_parent->curState==PlayingState)
      control_parent->player->kernel_seek( (value/100.0)*this->totaltime-this->currenttime);
    if(control_parent->curState== PausedState)
       control_parent->player->kernel_seek_pausing((value/100.0)*this->totaltime-this->currenttime);

    this->currenttime=(value/100.0)*this->totaltime;

    emit UpdateTime();

}


 void SeekBar::seek_only_pause(int value)
 {
     if(abs((value/100.0)*this->totaltime-this->currenttime)>10)
        {
          control_parent->player->kernel_seek_pausing((value/100.0)*this->totaltime-this->currenttime);
          this->currenttime=(value/100.0)*this->totaltime;
        }


      emit UpdateTime();

 }
 void SeekBar::change_is_pressed()
 {
     is_pressed=!is_pressed;
 }

void SeekBar::close_audio_for_slidermove()
  {

    if(is_pressed)
      {
         disconnect(this,SIGNAL(UpdateTime()),this,SLOT(UpdateSkin()));


      }
    else
    {
        connect(this,SIGNAL(UpdateTime()),this,SLOT(UpdateSkin()));

    }
      if( control_parent->curState==StartState||control_parent->curState==PlayingState)
           control_parent->player->kernel_pause();


  }

void SeekBar::UpdateSkin()
{
   this->currenttime=control_parent->player->kernel_currenttime;
   this->totaltime=control_parent->player->kernel_totaltime;

   click_bar->setValue(this->currenttime/this->totaltime*100.0);

 QString  min=QString("%1").arg(((int)this->currenttime)/60,2,10,QChar('0'));
 QString   sec=QString("%1").arg(((int)this->currenttime)%60,2,10,QChar('0'));

   edit_current_time->setText(min+":"+sec);


   QString  min2=QString("%1").arg(((int)this->totaltime)/60,2,10,QChar('0'));
   QString   sec2=QString("%1").arg(((int)this->totaltime)%60,2,10,QChar('0'));

   edit_total_time->setText(min2+":"+sec2);





}


ClickBar::ClickBar(SeekBar *parent)
{
  setMouseTracking(true);
  this->parent=parent;

}


ClickBar::~ClickBar()
{

}





void ClickBar::mousePressEvent(QMouseEvent *ev)
{
    //注意应先调用父类的鼠标点击处理事件，这样可以不影响拖动的情况   ？？？
    QSlider::mousePressEvent(ev);


    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum())+ minimum() );
    emit value_changed_by_click(pos * (maximum() - minimum())+ minimum() );

    //向父窗口发送自定义事件event type，这样就可以在父窗口中捕获这个事件进行处理
          QEvent evEvent(static_cast<QEvent::Type>(QEvent::User + 1));
          QCoreApplication::sendEvent(parentWidget(), &evEvent);

}


void ClickBar::mouseMoveEvent(QMouseEvent *ev)
{
   QSlider::mouseMoveEvent(ev);


    double value;
     double pos = ev->pos().x() / (double)width();
     value=pos * (maximum() - minimum())+ minimum();

     QString  min=QString("%1").arg(((int)((value/100.0)*parent->totaltime))/60,2,10,QChar('0'));
     QString  sec=QString("%1").arg(((int)((value/100.0)*parent->totaltime))%60,2,10,QChar('0'));

     QToolTip::showText(mapToGlobal(ev->pos()) ,min+":"+sec);

}
