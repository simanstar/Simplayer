#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
#include <QtWidgets>
#include "../playkernel/SimPlayer.h"
#include "../base/BaseConstant.h"

namespace Ui {
class ControlPanel;

}
class ControlPanel : public  QWidget,public BaseConstant
{
    Q_OBJECT
public:
    explicit ControlPanel(SimPlayer *player);
    ~ControlPanel();
    State curState; //播放状态,初始为停止
    SimPlayer *player;     //拥有线程指针，可控制该线程
public slots:
          void stateChanging();
signals:

    void stateChanged(State state); //播放状态发生改变

private:
      Ui::ControlPanel  *controlpanel_ui;







private slots:
    void updateButton();       //更新play按钮外观


    void play();  //播放
    void pause();  //暂停
    void stop();   //停止


    void seek_forward();      //快进
    void seek_backward();   //快退


    void setVolume (int value); //设置音量  （0-128）
    void setMute();             //设置静音

    void change_media(QString item);



};
#endif // CONTROLPANEL_H
