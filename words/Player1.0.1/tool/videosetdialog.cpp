#include "videosetdialog.h"

VideoSetDialog::VideoSetDialog(QWidget *parent)
{
 //   this->setWindowIcon(QIcon("synchronize.png"));
    this->setWindowTitle(tr("画质"));
  //  this->setWindowOpacity(0.5);

    defaultRadio=new QRadioButton(tr("原画质"),this);
    grayRadio=new QRadioButton(tr("灰画质"),this);

    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(defaultRadio);
    mainLayout->addWidget(grayRadio);
    this->setLayout(mainLayout);

    connect(defaultRadio, SIGNAL(clicked(bool)), this, SLOT(valueChanged()));
    connect(grayRadio, SIGNAL(clicked(bool)), this, SLOT(valueChanged()));
}

void VideoSetDialog::setSimPlayer(SimPlayer *simPlayer)
{
    this->simPlayer=simPlayer;
}

void VideoSetDialog::valueChanged()
{
    if (sender() ==defaultRadio)
       {
           simPlayer->isGray=false;
       }
    else if (sender() ==grayRadio)
       {
           simPlayer->isGray=true;
       }

}
