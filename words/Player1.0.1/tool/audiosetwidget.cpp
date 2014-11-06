#include"audiosetwidget.h"


AudioSetWidget::AudioSetWidget(QWidget *parent)
{

    leftChannelRadio=new QRadioButton(tr("左声道"),this);
    stereoChannelRadio=new QRadioButton(tr("立体声"),this);
    rightChannelRadio=new QRadioButton(tr("右声道"),this);

    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(leftChannelRadio);
    mainLayout->addWidget(stereoChannelRadio);
    mainLayout->addWidget(rightChannelRadio);
    this->setLayout(mainLayout);

    connect(leftChannelRadio, SIGNAL(clicked(bool)), this, SLOT(setChannel()));
     connect(stereoChannelRadio, SIGNAL(clicked(bool)), this, SLOT(setChannel()));
     connect(stereoChannelRadio, SIGNAL(clicked(bool)), this, SLOT(setChannel()));
}

void AudioSetWidget::setChannel()
{
    if (sender() ==leftChannelRadio)
       {
           SimPlayer::gTrack=1;
       }
       else if (sender() == stereoChannelRadio)
       {
           SimPlayer::gTrack=0;
       }
       else if (sender() == rightChannelRadio)
       {
           SimPlayer::gTrack=2;
       }

}
