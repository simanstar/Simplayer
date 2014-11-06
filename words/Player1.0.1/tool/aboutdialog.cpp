#include<QtWidgets>
#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : Dialog(parent)
{

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    this->setStyleSheet(" QPushButton{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0);font:bold 12px;}"
                                 "QPushButton:hover{background-color:rgb(123,124,122,80);}");

    writeTextInfo();
    createListWidget();
    createStackedLayout();
    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedLayout, SLOT(setCurrentIndex(int)));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 3);
    mainLayout->addWidget(listWidget, 0, 0);
    mainLayout->addLayout(stackedLayout, 0, 1);
    mainLayout->addWidget(buttonBox, 1, 0, 1, 2);
    setLayout(mainLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setWindowTitle(tr("about"));
    listWidget->setCurrentRow(0);
}
void AboutDialog::createListWidget()
{
    listWidget = new QListWidget(this);
    listWidget->addItem(tr("Version Info"));
    listWidget->addItem(tr("Introduction"));
    listWidget->setStyleSheet(" QListWidget{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");
}
void AboutDialog::createStackedLayout()
{
    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(textBrowser0);
    stackedLayout->addWidget(textBrowser1);
}
void AboutDialog::writeTextInfo()
{
    textBrowser0=new QTextBrowser(this);
    textBrowser0->append("版本:1.0.0\n产品名称:一生所爱\n版权归史文星与王号召所有\n联系方式qq：2073977858");
    textBrowser0->setStyleSheet(" QTextBrowser{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");

    textBrowser1=new QTextBrowser(this);
    textBrowser1->append("使用方法略，建议自己尝试");
    textBrowser1->setStyleSheet(" QTextBrowser{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");
}
