/********************************************************************************
** Form generated from reading UI file 'OpeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPEWIDGET_H
#define UI_OPEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpeWidget
{
public:

    void setupUi(QWidget *OpeWidget)
    {
        if (OpeWidget->objectName().isEmpty())
            OpeWidget->setObjectName(QString::fromUtf8("OpeWidget"));
        OpeWidget->resize(400, 300);

        retranslateUi(OpeWidget);

        QMetaObject::connectSlotsByName(OpeWidget);
    } // setupUi

    void retranslateUi(QWidget *OpeWidget)
    {
        OpeWidget->setWindowTitle(QCoreApplication::translate("OpeWidget", "OpeWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpeWidget: public Ui_OpeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPEWIDGET_H
