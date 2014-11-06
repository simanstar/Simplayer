#include <QApplication>
#include "./mainform/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *w = new MainWindow();
//   w->setWindowFlags(Qt::FramelessWindowHint);
     w->show();



    return app.exec();
}

