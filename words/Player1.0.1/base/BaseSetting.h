#ifndef BASESETTING_H
#define BASESETTING_H
class QString;

class BaseSetting
{
public:
    BaseSetting();
    static void readSettings();
    static void writeSettings();

    static void setSnapShotUrl(QString &string);
    static QString getSnapShotUrl();

    static void setOpenFileUrl(QString &string);
    static QString getOpenFileUrl();
    static QString getbackGroundImage();
    static void setBackgroundImage(QString &image);
private:
    static QString snapShotUrl;
    static QString openFileUrl;
    static QString backgroundImage;
    enum
    {
      MagicNumber = 0x7F51C883
    };
};


#endif // BASESETTING_H
