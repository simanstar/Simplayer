#ifndef PLAYLABEL_H
#define PLAYLABEL_H
#include <QtWidgets>
#include "SimPlayer.h"

class PlayLabel : public QLabel
{
     Q_OBJECT
public:
    PlayLabel(QWidget *parent=0);
    ~PlayLabel();
    void setPlayer(SimPlayer *player);

protected:

   void paintEvent(QPaintEvent *e);

private:

   SimPlayer *player;

private slots:
   void display();
};



#endif // PLAYLABEL_H
