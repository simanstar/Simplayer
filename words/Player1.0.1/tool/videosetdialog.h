#ifndef VIDEOSETDIALOG_H
#define VIDEOSETDIALOG_H
#include <QDialog>
#include <QtWidgets>
#include "../playkernel/SimPlayer.h"
class QRadioButton;
class VideoSetDialog:public QWidget
{
    Q_OBJECT
public:
    VideoSetDialog(QWidget *parent=0);
    void setSimPlayer(SimPlayer *simPlayer);
private slots:
    void valueChanged();
private:
    QRadioButton *defaultRadio;
    QRadioButton *grayRadio;

    SimPlayer *simPlayer;
};
#endif // VIDEOSETDIALOG_H
