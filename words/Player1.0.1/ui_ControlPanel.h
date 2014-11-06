/********************************************************************************
** Form generated from reading UI file 'ControlPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPanel
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *backward;
    QToolButton *play;
    QToolButton *forward;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *volume;
    QSlider *horizontalSlider;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ControlPanel)
    {
        if (ControlPanel->objectName().isEmpty())
            ControlPanel->setObjectName(QStringLiteral("ControlPanel"));
        ControlPanel->resize(335, 108);
        ControlPanel->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(ControlPanel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        backward = new QToolButton(ControlPanel);
        backward->setObjectName(QStringLiteral("backward"));
        backward->setMinimumSize(QSize(30, 30));
        backward->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"  border-image: url(:/images/back.png);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	border-image: url(:/images/backward_pressed.png);\n"
"}"));

        horizontalLayout_2->addWidget(backward);

        play = new QToolButton(ControlPanel);
        play->setObjectName(QStringLiteral("play"));
        play->setMinimumSize(QSize(34, 34));
        play->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(play);

        forward = new QToolButton(ControlPanel);
        forward->setObjectName(QStringLiteral("forward"));
        forward->setMinimumSize(QSize(32, 30));
        forward->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"  border-image: url(:/images/forward.png);\n"
"\n"
"}\n"
"QToolButton:pressed\n"
"{\n"
"\n"
"	border-image: url(:/images/forward_pressed.png);\n"
"}\n"
"\n"
""));

        horizontalLayout_2->addWidget(forward);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        volume = new QToolButton(ControlPanel);
        volume->setObjectName(QStringLiteral("volume"));
        volume->setMinimumSize(QSize(30, 25));
        volume->setBaseSize(QSize(25, 15));
        volume->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(volume);

        horizontalSlider = new QSlider(ControlPanel);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(0, 0));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(ControlPanel);

        QMetaObject::connectSlotsByName(ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *ControlPanel)
    {
        ControlPanel->setWindowTitle(QApplication::translate("ControlPanel", "Form", 0));
        backward->setText(QString());
        play->setText(QString());
        forward->setText(QString());
        volume->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ControlPanel: public Ui_ControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPANEL_H
