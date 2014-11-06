#include "titlebar.h"

TitleBar::TitleBar(QMainWindow *parent)
{
    // 不继承父组件的背景色
  //  setAutoFillBackground(true);
    // 使用 Highlight 作为背景色
   // setBackgroundRole(QPalette::Highlight);
    this->mainWindow=parent;

    minimize = new QToolButton(this);
    maximize = new QToolButton(this);
    close= new QToolButton(this);

    // 设置按钮图像的样式
//    QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
//    close->setIcon(pix);

//    maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
//    maximize->setIcon(maxPix);

//    pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
//    minimize->setIcon(pix);

//    restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

    QPixmap min_pix(":/images/min.png");
    QPixmap max_pix(":/images/max.png");
    QPixmap close_pix(":/images/close.png");

    this->setStyleSheet("margin-left:5px;");
    minimize->setMask(min_pix.createHeuristicMask());
    minimize->setStyleSheet("QToolButton{border-image:url(:/images/min.png);}"
                            "QToolButton:pressed{border-image:url(:/images/min_pressed.png)}");

    maximize->setMask(max_pix.createHeuristicMask());
    maximize->setStyleSheet("QToolButton{border-image:url(:/images/max.png);}"
                            "QToolButton:pressed{border-image:url(:/images/max_pressed.png)}");

    close->setMask(close_pix.createHeuristicMask());
    close->setStyleSheet("QToolButton{border-image:url(:/images/close.png);}"
                         "QToolButton:pressed{border-image:url(:/images/close_pressed.png)}");







  minimize->setMinimumSize(23,23);
  maximize->setMinimumSize(23,23);
  close->setMinimumSize(23,23);




//    QLabel *label = new QLabel(this);
//    label->setText("Window Title");

    QHBoxLayout *hbox = new QHBoxLayout(this);

    //hbox->addWidget(label);
    hbox->addWidget(minimize);
    hbox->addWidget(maximize);
    hbox->addWidget(close);

    hbox->insertStretch(0, 50);
    hbox->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setLayout(hbox);

    maxNormal = false;

    connect(close, SIGNAL( clicked(bool) ), mainWindow, SLOT(close() ) );
    connect(minimize, SIGNAL( clicked(bool) ), this, SLOT(showSmall() ) );
    connect(maximize, SIGNAL( clicked(bool) ), this, SLOT(showMaxRestore() ) );
}

void TitleBar::showSmall()
{
   //this->parentWidget()->showMinimized();
    mainWindow->showMinimized();
}

void TitleBar::showMaxRestore()
{
    if (maxNormal) {
        mainWindow->showNormal();
        maxNormal = !maxNormal;
     //   maximize->setIcon(maxPix);
    } else {
        mainWindow->showMaximized();
        maxNormal = !maxNormal;
       // maximize->setIcon(restorePix);
    }
}

void TitleBar::mousePressEvent(QMouseEvent *me)
{
    startPos = me->globalPos();
    clickPos = mapToParent(me->pos());
}
void TitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if (maxNormal)
        return;
    mainWindow->move(me->globalPos() - clickPos);
}
