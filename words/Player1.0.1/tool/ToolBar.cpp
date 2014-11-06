#include "ToolBar.h"
#include "../base/BaseSetting.h"

ToolBar::ToolBar(QWidget *parent)
{
    createButtons();

    QHBoxLayout *hLayout=new QHBoxLayout;
    hLayout->addWidget(openButton);
 //   hLayout->setSpacing(0);
    hLayout->addWidget(snapShotButton);
  //  hLayout->setSpacing(0);
    hLayout->addWidget(rotateButton);
  //  hLayout->setSpacing(0);
    hLayout->addWidget(synchronizeButton);
  //  hLayout->setSpacing(0);
  //
    hLayout->addWidget(adjustButton);
    hLayout->addWidget(aboutButton);

    hLayout->insertStretch(0, 500);
    hLayout->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->setLayout(hLayout);
    resize(200,200);
}

void ToolBar::setSimPlayer(SimPlayer *simPlayer)
{
    this->simPlayer=simPlayer;
}

//信号openAction的槽函数open（）
void ToolBar::openFile()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                    tr("Open av file"), BaseSetting::getOpenFileUrl(),tr("(*.*)"));
    if (!fileList.isEmpty())
    {
        //保存这次打开的路径

        QString  file_path;
        QFileInfo fi;
        fi=QFileInfo(fileList.at(0));
        file_path = fi.absolutePath();
        BaseSetting::setOpenFileUrl(file_path);
        emit addNewFile(&fileList);
     //  player->filePath=fileName.toStdString().c_str();
    }

}
//截图槽
void ToolBar::snapShot()
{
    ScreenShoot* instance = ScreenShoot::Instance();
    instance->setSimPlayer(simPlayer);
    if(simPlayer->isExisted())
    {
        if(simPlayer->isPlaying())
        {
            simPlayer->kernel_pause();
            instance->setPlayStateChanged(true);
        }
    }
    instance->show();
}
void ToolBar::rotate()
{
    simPlayer->rotateScreen();
}
//音视频同步槽
void ToolBar::synchronizeVideo()
{
    SynchronizeDialog *synchronizeDialog=new SynchronizeDialog(simPlayer);
    synchronizeDialog->show();
}

void ToolBar::adjustSet()
{
    AdjustDialog *adjustButton=new AdjustDialog(simPlayer);
    adjustButton->show();
}
//帮助信息槽
void ToolBar::aboutInfo()
{
    AboutDialog *aboutDialog=new AboutDialog(this);
    aboutDialog->show();
}


void ToolBar::createButtons()
{
    openButton=new QToolButton(this);
    snapShotButton=new QToolButton(this);
    rotateButton=new QToolButton(this);
    synchronizeButton=new QToolButton(this);
//    channelSetButton=new QToolButton(this);
//    videoSetButton=new QToolButton(this);
    adjustButton=new QToolButton(this);
    aboutButton=new QToolButton(this);

    //设置功能与快捷键提示
    openButton->setToolTip(tr("打开文件(Ctrl+o)"));
    snapShotButton->setToolTip(tr("截图(F6)"));
    rotateButton->setToolTip(tr("旋转屏幕(F7)"));
    synchronizeButton->setToolTip(tr("同步(F7)"));
    adjustButton->setToolTip(tr("调节(Alt+s)"));

    //自动浮现
    openButton->setAutoRaise(true);
    snapShotButton->setAutoRaise(true);
    rotateButton->setAutoRaise(true);
    synchronizeButton->setAutoRaise(true);
    adjustButton->setAutoRaise(true);
    aboutButton->setAutoRaise(true);

    //快捷键
    openButton->setShortcut(QKeySequence::Open);
    snapShotButton->setShortcut(tr("F6"));
    rotateButton->setShortcut(tr("F7"));
    synchronizeButton->setShortcut(tr("F8"));
    adjustButton->setShortcut(tr("Alt+s"));

    //设置大小,保持一致
//    openButton->setMinimumSize(20,20);
//    snapShotButton->setMinimumSize(20,20);
//    rotateButton->setMinimumSize(20,20);
//    synchronizeButton->setMinimumSize(20,20);
//    adjustButton->setMinimumSize(20,20);
//    aboutButton->setMinimumSize(20,20);


    openButton->setIcon(QIcon(":/images/open.png"));
    snapShotButton->setIcon(QIcon(":/images/snapshot.png"));
    rotateButton->setIcon(QIcon(":/images/rotate.png"));
    synchronizeButton->setIcon(QIcon(":/images/synchronize.png"));
    adjustButton->setIcon(QIcon(":/images/audioset.png"));
    aboutButton->setIcon(QIcon(":/images/about.png"));

    //连接槽
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(rotateButton,SIGNAL(clicked()),this,SLOT(rotate()));
    connect(snapShotButton,SIGNAL(clicked()),this,SLOT(snapShot()));
    connect(synchronizeButton,SIGNAL(clicked()),this,SLOT(synchronizeVideo()));
    connect(adjustButton,SIGNAL(clicked()),this,SLOT(adjustSet()));
    connect(aboutButton,SIGNAL(clicked()),this,SLOT(aboutInfo()));
}
