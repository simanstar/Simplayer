#ifndef SYNCHRONIZEDIALOG_H
#define SYNCHRONIZEDIALOG_H
#include <QDialog>
#include "../playkernel/SimPlayer.h"
#include "Dialog.h"

class QSlider;
class QLabel;
class QDialogButtonBox;
class SynchronizeDialog:public Dialog
{
   Q_OBJECT
public:
    SynchronizeDialog(SimPlayer *parent=0);
public slots:
    void syncValueChanged(int value);
private:
    QLabel *synchronizeLabel;
    QSlider *synchronizeSlider;
    QLabel *sliderLabel;

    SimPlayer *simPlayer;
    QDialogButtonBox *buttonBox;
};
#endif // SYNCHRONIZEDIALOG_H
