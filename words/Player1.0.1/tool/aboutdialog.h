#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include<QDialog>
#include <QWidget>
#include "Dialog.h"

class QStackedLayout;
class QListWidget;
class QTextBrowser;
class QDialogButtonBox;
class AboutDialog:public Dialog
{
public :
    AboutDialog(QWidget *parent=0);
private:
    void createListWidget();
    void createStackedLayout();
    void writeTextInfo();
private:
    QStackedLayout *stackedLayout;
    QListWidget *listWidget;
    QTextBrowser *textBrowser0;
    QTextBrowser *textBrowser1;
    QDialogButtonBox *buttonBox;
};
#endif // ABOUTDIALOG_H
