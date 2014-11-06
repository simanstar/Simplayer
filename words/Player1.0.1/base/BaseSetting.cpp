#include <QtWidgets>
#include "BaseSetting.h"

QString BaseSetting::snapShotUrl="";
QString BaseSetting::openFileUrl="";
QString BaseSetting::backgroundImage=":/images/sky.jpg";

BaseSetting::BaseSetting()
{

}

void BaseSetting::readSettings()
{
    QFile file("setting");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_1);

    quint32 magic;
    in >> magic;
    if (magic != MagicNumber) {
//        QMessageBox::warning(0, "setting",
//                             "The file is not a setting file.");
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    in>>snapShotUrl;
    in>>openFileUrl;
  //  in>>backgroundImage;
    QApplication::restoreOverrideCursor();
}

void BaseSetting::writeSettings()
{
    QString filename="setting";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
       return ;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_1);

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<snapShotUrl;
    out<<openFileUrl;
    out<<backgroundImage;
    QApplication::restoreOverrideCursor();
}

void BaseSetting::setSnapShotUrl(QString &string)
{
    snapShotUrl=string;
}
QString BaseSetting::getSnapShotUrl()
{
    return snapShotUrl;
}

void BaseSetting::setOpenFileUrl(QString &string)
{
    openFileUrl=string;
}
QString BaseSetting::getOpenFileUrl()
{
    return openFileUrl;
}


QString BaseSetting::getbackGroundImage()
{
    return backgroundImage;
}

void BaseSetting::setBackgroundImage(QString &image)
{
    backgroundImage=image;
}


