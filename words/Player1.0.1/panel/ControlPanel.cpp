#include "ControlPanel.h"
#include "ui_ControlPanel.h"
#include <QtGui/QPixmap>


ControlPanel::ControlPanel(SimPlayer *player) :

    controlpanel_ui (new Ui::ControlPanel)
{
    controlpanel_ui->setupUi(this);


    this->player=player;

     QPixmap pixmap(":/images/play.png");
     QPixmap pixmap2(":/images/back.png");
     QPixmap pixmap3(":/images/forward.png");
     QPixmap pixmap4(":/images/volume2.png");



     controlpanel_ui->play->setMask(pixmap.createHeuristicMask());
     controlpanel_ui->backward->setMask(pixmap2.createHeuristicMask());
     controlpanel_ui->forward->setMask(pixmap3.createHeuristicMask());
   //  controlpanel_ui->volume->setMask(pixmap4.createHeuristicMask());

      controlpanel_ui->volume->setStyleSheet("border-image: url(:/images/volume2.png);margin-top:-8px;");




    connect(controlpanel_ui->play,SIGNAL(clicked()),this,SLOT(stateChanging()));    //点击play按钮会引起状态改变

   // 需要获得状态改变信号的槽
    connect(this,SIGNAL(stateChanged(State)),this,SLOT(updateButton()));
    connect(this,SIGNAL(stateChanged(State)),this,SLOT(play()));
    connect(this,SIGNAL(stateChanged(State)),this,SLOT(pause()));
    connect(this,SIGNAL(stateChanged(State)),this,SLOT(stop()));
    connect(this,SIGNAL(stateChanged(State)),player,SLOT(setState(State)));

  //  快进快退
    connect(controlpanel_ui->backward,SIGNAL(clicked()),this,SLOT(seek_backward()));
    connect(controlpanel_ui->forward,SIGNAL(clicked()),this,SLOT(seek_forward()));


   // 声音条
    controlpanel_ui->horizontalSlider->setRange(0,128);
    connect(controlpanel_ui->volume,SIGNAL(clicked()),this,SLOT(setMute()));
    connect(controlpanel_ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(setVolume(int)));


    //初始值
      curState=StoppedState;
     emit stateChanged(curState);


}



ControlPanel::~ControlPanel()
{
    delete controlpanel_ui;
}


void ControlPanel::stateChanging()
{
    switch(this->curState)
    {
        case StoppedState:
        this->curState=StartState;
        break;
        case StartState:
        this->curState=PausedState;
        break;
        case PausedState:
        this->curState=PlayingState;
        break;
        case PlayingState:
        this->curState=PausedState;
        break;
        default:
        break;

    }

    emit stateChanged(curState);

}

void ControlPanel::updateButton()
{

    if(this->curState==StoppedState)


    controlpanel_ui->play->setStyleSheet("  QToolButton{border-image: url(:/images/play.png);}"
                                         " QToolButton:pressed{border-image: url(:/images/play_pressed.png);}");
    if(this->curState==StartState)


    controlpanel_ui->play->setStyleSheet(" QToolButton:pressed{border-image: url(:/images/pause_pressed.png);}"
                                         "  QToolButton{border-image: url(:/images/pause.png);}");
  if(this->curState==PausedState)


  controlpanel_ui->play->setStyleSheet(" QToolButton:pressed{border-image: url(:/images/play_pressed.png);}"
                                       "  QToolButton{border-image: url(:/images/play.png);}");

    if(this->curState==PlayingState)

    controlpanel_ui->play->setStyleSheet(" QToolButton:pressed{border-image: url(:/images/pause_pressed.png);} "
                                         " QToolButton{border-image: url(:/images/pause.png);}");
}
void ControlPanel::play()
{

    if(this->curState==StartState)
    {

           player->start();

    }
}

void ControlPanel::pause()
{
    if(this->curState==PausedState||this->curState==PlayingState)
    {

   player->kernel_pause();
    }

}


 void ControlPanel::stop()    //停止
 {
     if(this->curState==StoppedState)
        {


            player->kernel_stop() ;
            //要确保进程已经停止
            if(player->isRunning())
              {

                 player->wait(800);

               }

          }








 }


 void ControlPanel::setVolume(int value)
 {
       player->volume=value;
       controlpanel_ui->volume->setStyleSheet("border-image: url(:/images/volume2.png);margin-top:-8px;");
 }

 void ControlPanel::setMute()
 {   if(player->volume)
        {

         player->volume=0;
         controlpanel_ui->volume->setStyleSheet("border-image: url(:/images/volume1.png);margin-top:-8px;");

        }

     else
     {
          player->volume=controlpanel_ui->horizontalSlider->value();
        controlpanel_ui->volume->setStyleSheet("border-image: url(:/images/volume2.png);margin-top:-8px;");

     }
 }

 void ControlPanel::seek_forward()
 {

     if(this->curState==PausedState)
     {
        player->kernel_seek_pausing(15);
     }


       else
     {   player->kernel_seek(15);

     }
 }


 void ControlPanel::seek_backward()
 {
     if(this->curState==PausedState)
     {
        player->kernel_seek_pausing(-15);
     }
      else
     {
         player->kernel_seek(-15);        //向后5秒
     }
 }



  void ControlPanel::change_media(QString item)
  {


      if(this->curState!=StoppedState)
      {

        this->curState=StoppedState;
        emit stateChanged(curState);


      }

          player->filepath=item;
          this->curState=StartState;
          emit stateChanged(curState);




  }


