#include "adjustdialog.h"

AdjustDialog::AdjustDialog(SimPlayer *parent)
{

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    this->setStyleSheet(" QPushButton{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0);font:bold 12px;}"
                                 "QPushButton:hover{background-color:rgb(123,124,122,80);}");

    audioSetWidget=new AudioSetWidget(this);
    audioSetWidget->setStyleSheet(" QWidget{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");
    videoSetDialog=new VideoSetDialog(this);
    videoSetDialog->setStyleSheet(" QWidget{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");
    videoSetDialog->setSimPlayer(parent);

    tabWidget=new QTabWidget(this);
    tabWidget->addTab(audioSetWidget,trUtf8("音频设置"));
    tabWidget->addTab(videoSetDialog,trUtf8("视频设置"));
    tabWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    QString tabBarStyle = "QTabBar::tab {min-width:8px;color: white;border: 2px solid #F5F5F6;border-top-left-radius: 6px;border-top-right-radius: 6px;padding:3px;}	\
                           QTabBar::tab:!selected {margin-top: 3px;} \
                           QTabBar::tab:selected {color: blue;}";
    tabWidget->setStyleSheet(tabBarStyle);


    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *vbox=new QVBoxLayout(this);
    vbox->addWidget(tabWidget);
    vbox->addWidget(buttonBox);
    this->setLayout(vbox);
}

