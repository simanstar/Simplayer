#ifndef TITLEBAR_H
#define TITLEBAR_H
#include <QtWidgets>
#include <QMainWindow>


class TitleBar : public QWidget
{
    Q_OBJECT
public:
    TitleBar(QMainWindow *parent=0);
public slots:
    void showSmall();
    void showMaxRestore();
protected:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
private:
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;

    QMainWindow *mainWindow;
};
#endif // TITLEBAR_H
