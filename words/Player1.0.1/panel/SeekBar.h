#ifndef SEEKBAR_H
#define SEEKBAR_H
#include <QtWidgets>

#include <QThread>

#include "ControlPanel.h"

class ClickBar ;

class SeekBar : public QWidget
{
    Q_OBJECT
public:
    explicit SeekBar(ControlPanel *parent);
    ~SeekBar();

    enum State         //表示播放状态的值
    {
        PlayingState,
        PausedState,
        StoppedState,
        StartState
    };

    float totaltime;      //总时间   以秒为单位
    float currenttime;     //当前时间    以秒为单位
    int is_pressed;
private:
    ClickBar *click_bar;
    QLabel *edit_current_time;
    QLabel *edit_total_time;


    ControlPanel *control_parent;          //指向它的父亲的指针

private slots:
      void UpdateSkin();
      void seek(int value);
      void seek_only_pause(int value);
      void close_audio_for_slidermove();
      void set_value(int value);
      void change_is_pressed();

signals:
      void UpdateTime();
protected:





};

class ClickBar : public QSlider
{
    Q_OBJECT
public:
    explicit ClickBar(SeekBar *parent);
    ~ClickBar();
private:

    SeekBar *parent;




protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

signals:
    void value_changed_by_click(int);




};
#endif // SEEKBAR_H
