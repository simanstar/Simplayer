  HEADERS += \
    mainform/MainWindow.h \
    mainform/ContralWidget.h \
    mainform/CentralWidget.h \
    panel/ui_SeekBar.h \
    panel/ui_ControlPanel.h \
    panel/SeekBar.h \
    panel/ControlPanel.h \
    playkernel/SimPlayer.h \
    playkernel/PlayLabel.h \
    playkernel/my_kernel.h \
    playlist/PlayList.h \
    tool/ToolBar.h \
    tool/synchronizedialog.h \
    tool/screenshot.h \
    tool/FrameWidget.h \
    tool/audiosetwidget.h \
    tool/aboutdialog.h \
    tool/videosetdialog.h \
    title/titlebar.h \
    tool/adjustdialog.h \
    tool/Dialog.h \
    base/BaseConstant.h \
    base/BaseSetting.h

SOURCES += \
    main.cpp \
    mainform/MainWindow.cpp \
    mainform/ContralWidget.cpp \
    panel/SeekBar.cpp \
    panel/ControlPanel.cpp \
    playkernel/SimPlayer.cpp \
    playkernel/PlayLabel.cpp \
    playlist/PlayList.cpp \
    tool/ToolBar.cpp \
    tool/synchronizedialog.cpp \
    tool/screenshot.cpp \
    tool/FrameWidget.cpp \
    tool/audiosetwidget.cpp \
    tool/aboutdialog.cpp \
    tool/videosetdialog.cpp \
    title/titlebar.cpp \
    tool/adjustdialog.cpp \
    tool/Dialog.cpp \
    base/BaseConstant.cpp \
    base/BaseSetting.cpp \
    mainform/CentralWidget.cpp


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




INCLUDEPATH +=  SDL/include


INCLUDEPATH +=  ffmpeg/include
LIBS += ffmpeg/lib/avcodec.lib\
        ffmpeg/lib/avdevice.lib \
        ffmpeg/lib/avfilter.lib \
        ffmpeg/lib/avformat.lib \
        ffmpeg/lib/avutil.lib \
          ffmpeg/lib/libmysql.lib\
        ffmpeg/lib/postproc.lib\
         ffmpeg/lib/SDL.lib\
          ffmpeg/lib/swresample.lib\
           ffmpeg/lib/swscale.lib\


QT += core gui widgets  multimedia multimediawidgets serialport
QT +=multimedia

FORMS += \
    panel/ControlPanel.ui

RESOURCES += \
    images.qrc \
    qss.qrc \
    resources.qrc


RC_FILE += windowexe.rc
