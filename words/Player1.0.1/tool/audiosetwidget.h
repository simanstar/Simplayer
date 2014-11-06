#ifndef AUDIOSETWIDGET_H
#define AUDIOSETWIDGET_H
#include <QtWidgets>
#include "../playkernel/SimPlayer.h"

class QRadioButton;
class AudioSetWidget:public QWidget
{
    Q_OBJECT
public:
    AudioSetWidget(QWidget *parent=0);
private slots:
    void setChannel();
private:
    QRadioButton *leftChannelRadio;
    QRadioButton *stereoChannelRadio;
    QRadioButton *rightChannelRadio;
};
#endif // AUDIOSETWIDGET_H
