#include "PlayLabel.h"
#include "my_kernel.h"



PlayLabel::PlayLabel(QWidget *parent){

    this->setUpdatesEnabled(false);

}




PlayLabel::~PlayLabel(){

}

void PlayLabel::setPlayer(SimPlayer *player)
{
    this->player=player;
}

 void PlayLabel::display()
 {

     this->setUpdatesEnabled(true);
     this->update();


 }



void PlayLabel::paintEvent(QPaintEvent *e)
{
     QPixmap pixmap;
     QPixmap pixmap_temp;
     QPainter painter(this);



     if(player->global_video_state->videoStream<0)  //MP3临时
       {

         QPixmap pix_mp3(":/images/mp3_pixmap.jpeg");
         painter.drawPixmap(0,0,pix_mp3.scaled(this->size()));
         return ;//直接跳过以下的

       }
     if(player->out_buffer==NULL)     //out_buffer未分配直接退出
        {

            return;
        }
     QImage  tmpImage((uchar *)player->out_buffer,player->global_video_state->video_st->codec->width,player->global_video_state->video_st->codec->height,QImage::Format_RGB888 );
      QImage  image = tmpImage.copy();
     //  QPixmap  pixmap = QPixmap::fromImage(image.scaled(this->playlabel->size(), Qt::KeepAspectRatio) );





         if(!player->isGray)
         {
               pixmap_temp = QPixmap::fromImage(image);
             pixmap=pixmap_temp.scaled(this->size());
         }
         else
         {
             pixmap=player->imageGray(image,0,this->width(),this->height());
         }
         if(player->rotateAngle!=0)
         {
           //  this->playlabel->setPixmap(pixmap.transformed(*leftmatrix,Qt::SmoothTransformation));
               painter.drawPixmap(0,0,pixmap.transformed(*player->leftmatrix,Qt::SmoothTransformation));
         }
         else
         {
           //  this->playlabel->setPixmap(pixmap);
             painter.drawPixmap(0,0,pixmap);
         }
}



