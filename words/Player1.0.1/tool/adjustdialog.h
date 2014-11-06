#ifndef ADJUSTDIALOG_H
#define ADJUSTDIALOG_H
#include <QDialog>
#include "../playkernel/SimPlayer.h"
#include "audiosetwidget.h"
#include "videosetdialog.h"
#include "Dialog.h"

class QTableWidget;
class QDialogButtonBox;
class AdjustDialog:public Dialog
{
public:
    AdjustDialog(SimPlayer *parent);
private:
    AudioSetWidget *audioSetWidget;
    VideoSetDialog *videoSetDialog;
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};


#endif // ADJUST_H
