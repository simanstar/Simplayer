#include <QtWidgets>
#include "synchronizedialog.h"

SynchronizeDialog::SynchronizeDialog(SimPlayer *parent)
{

    this->simPlayer=parent;

    this->setWindowIcon(QIcon("synchronize.png"));
    this->setWindowTitle(tr("同步"));
    this->setWindowOpacity(0.5);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    this->setStyleSheet(" QPushButton{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0);font:bold 12px;}"
                                 "QPushButton:hover{background-color:rgb(123,124,122,80);}");

    synchronizeLabel=new QLabel(tr("音视频时间差"));

    synchronizeSlider=new QSlider(Qt::Horizontal,this);
    synchronizeSlider->setMinimum(-100);
    synchronizeSlider->setMaximum(100);

    sliderLabel=new QLabel;
    sliderLabel->setText("0");

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->addWidget(synchronizeLabel);
    mainLayout->addWidget(synchronizeSlider);
    mainLayout->addWidget(sliderLabel);

    QVBoxLayout *vbox=new QVBoxLayout;
    vbox->addLayout(mainLayout);
    vbox->addWidget(buttonBox);

    this->setLayout(vbox);

    connect(synchronizeSlider,SIGNAL(valueChanged(int)),this,SLOT(syncValueChanged(int)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}
void SynchronizeDialog::syncValueChanged(int value)
{
    simPlayer->synchronizeDleta=value/10;
    sliderLabel->setNum(value);
}
