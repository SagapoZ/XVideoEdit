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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
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
    QSlider *playSlider;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *bright;
    QDoubleSpinBox *contrast;
    QPushButton *setBt;
    XVideoWidget *des;
    QPushButton *exportBt;

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
"QLabel\n"
"{\n"
"	\n"
"	background-color: rgb(255, 255, 255);\n"
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
        openBt->setGeometry(QRect(420, 340, 81, 31));
        openBt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        playSlider = new QSlider(XVideoUIClass);
        playSlider->setObjectName(QString::fromUtf8("playSlider"));
        playSlider->setGeometry(QRect(10, 340, 381, 22));
        playSlider->setMaximum(999);
        playSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(XVideoUIClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(430, 390, 91, 21));
        label_2 = new QLabel(XVideoUIClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(400, 420, 121, 21));
        bright = new QSpinBox(XVideoUIClass);
        bright->setObjectName(QString::fromUtf8("bright"));
        bright->setGeometry(QRect(530, 390, 101, 22));
        contrast = new QDoubleSpinBox(XVideoUIClass);
        contrast->setObjectName(QString::fromUtf8("contrast"));
        contrast->setGeometry(QRect(530, 420, 101, 22));
        contrast->setMinimum(1.000000000000000);
        contrast->setMaximum(3.990000000000000);
        setBt = new QPushButton(XVideoUIClass);
        setBt->setObjectName(QString::fromUtf8("setBt"));
        setBt->setGeometry(QRect(690, 390, 81, 31));
        setBt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        des = new XVideoWidget(XVideoUIClass);
        des->setObjectName(QString::fromUtf8("des"));
        des->setGeometry(QRect(400, 50, 380, 280));
        exportBt = new QPushButton(XVideoUIClass);
        exportBt->setObjectName(QString::fromUtf8("exportBt"));
        exportBt->setGeometry(QRect(540, 340, 81, 31));
        exportBt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(XVideoUIClass);
        QObject::connect(closeBt, SIGNAL(clicked()), XVideoUIClass, SLOT(close()));
        QObject::connect(openBt, SIGNAL(clicked()), XVideoUIClass, SLOT(Open()));
        QObject::connect(playSlider, SIGNAL(sliderPressed()), XVideoUIClass, SLOT(SliderPress()));
        QObject::connect(playSlider, SIGNAL(sliderReleased()), XVideoUIClass, SLOT(SliderRelease()));
        QObject::connect(playSlider, SIGNAL(sliderMoved(int)), XVideoUIClass, SLOT(SetPos(int)));
        QObject::connect(setBt, SIGNAL(clicked()), XVideoUIClass, SLOT(Set()));
        QObject::connect(exportBt, SIGNAL(clicked()), XVideoUIClass, SLOT(Export()));

        QMetaObject::connectSlotsByName(XVideoUIClass);
    } // setupUi

    void retranslateUi(QWidget *XVideoUIClass)
    {
        XVideoUIClass->setWindowTitle(QApplication::translate("XVideoUIClass", "XVideoUI", nullptr));
        closeBt->setText(QString());
        minBt->setText(QString());
        maxBt->setText(QString());
        openBt->setText(QApplication::translate("XVideoUIClass", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        label->setText(QApplication::translate("XVideoUIClass", "\344\272\256\345\272\246[0-100]", nullptr));
        label_2->setText(QApplication::translate("XVideoUIClass", "\345\257\271\346\257\224\345\272\246[1.0-3.0]", nullptr));
        setBt->setText(QApplication::translate("XVideoUIClass", "\350\256\276\347\275\256", nullptr));
        exportBt->setText(QApplication::translate("XVideoUIClass", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XVideoUIClass: public Ui_XVideoUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XVIDEOUI_H
