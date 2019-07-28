/********************************************************************************
** Form generated from reading UI file 'XVideoUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XVIDEOUI_H
#define UI_XVIDEOUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "xvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_XVideoUIClass
{
public:
    QPushButton *closeBt;
    QPushButton *minBt;
    QPushButton *maxBt;
    XVideoWidget *src1video;
    QPushButton *openBt;

    void setupUi(QWidget *XVideoUIClass)
    {
        if (XVideoUIClass->objectName().isEmpty())
            XVideoUIClass->setObjectName(QString::fromUtf8("XVideoUIClass"));
        XVideoUIClass->resize(800, 600);
        XVideoUIClass->setStyleSheet(QString::fromUtf8("#XVideoUIClass\n"
"{\n"
"	\n"
"	background-color: rgb(53, 53, 53);\n"
"}\n"
"#closeBt\n"
"{\n"
"	border-image: url(:/Resources/close.png);\n"
"}\n"
"#closeBt:hover\n"
"{\n"
"	border-image: url(:/Resources/close_hover.png);\n"
"}\n"
"#minBt\n"
"{\n"
"border-image: url(:/Resources/min.png);\n"
"}\n"
"#minBt:hover\n"
"{\n"
"border-image: url(:/Resources/min_hover.png);\n"
"}\n"
"#maxBt\n"
"{\n"
"	\n"
"	border-image: url(:/Resources/max.png);\n"
"}\n"
"#maxBt:hover\n"
"{\n"
"	\n"
"	border-image: url(:/Resources/max_hover.png);\n"
"}\n"
""));
        closeBt = new QPushButton(XVideoUIClass);
        closeBt->setObjectName(QString::fromUtf8("closeBt"));
        closeBt->setGeometry(QRect(1, 4, 34, 34));
        minBt = new QPushButton(XVideoUIClass);
        minBt->setObjectName(QString::fromUtf8("minBt"));
        minBt->setGeometry(QRect(36, 4, 32, 32));
        maxBt = new QPushButton(XVideoUIClass);
        maxBt->setObjectName(QString::fromUtf8("maxBt"));
        maxBt->setGeometry(QRect(70, 4, 32, 32));
        src1video = new XVideoWidget(XVideoUIClass);
        src1video->setObjectName(QString::fromUtf8("src1video"));
        src1video->setGeometry(QRect(10, 50, 380, 280));
        openBt = new QPushButton(XVideoUIClass);
        openBt->setObjectName(QString::fromUtf8("openBt"));
        openBt->setGeometry(QRect(460, 360, 81, 31));
        openBt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(XVideoUIClass);
        QObject::connect(closeBt, SIGNAL(clicked()), XVideoUIClass, SLOT(close()));
        QObject::connect(openBt, SIGNAL(clicked()), XVideoUIClass, SLOT(Open()));

        QMetaObject::connectSlotsByName(XVideoUIClass);
    } // setupUi

    void retranslateUi(QWidget *XVideoUIClass)
    {
        XVideoUIClass->setWindowTitle(QApplication::translate("XVideoUIClass", "XVideoUI", nullptr));
        closeBt->setText(QString());
        minBt->setText(QString());
        maxBt->setText(QString());
        openBt->setText(QApplication::translate("XVideoUIClass", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XVideoUIClass: public Ui_XVideoUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XVIDEOUI_H
