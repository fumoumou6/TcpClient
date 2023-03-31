/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *name_lab;
    QLineEdit *name_le;
    QLabel *pwd_lab;
    QLineEdit *pwd_le;
    QPushButton *login_pb;
    QHBoxLayout *horizontalLayout;
    QPushButton *regist_pb;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel_pb;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName(QString::fromUtf8("TcpClient"));
        TcpClient->resize(800, 600);
        QFont font;
        font.setPointSize(22);
        TcpClient->setFont(font);
        gridLayout_2 = new QGridLayout(TcpClient);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 178, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(199, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        name_lab = new QLabel(TcpClient);
        name_lab->setObjectName(QString::fromUtf8("name_lab"));

        gridLayout->addWidget(name_lab, 0, 0, 1, 1);

        name_le = new QLineEdit(TcpClient);
        name_le->setObjectName(QString::fromUtf8("name_le"));

        gridLayout->addWidget(name_le, 0, 1, 1, 1);

        pwd_lab = new QLabel(TcpClient);
        pwd_lab->setObjectName(QString::fromUtf8("pwd_lab"));
        pwd_lab->setLocale(QLocale(QLocale::Chinese, QLocale::China));

        gridLayout->addWidget(pwd_lab, 1, 0, 1, 1);

        pwd_le = new QLineEdit(TcpClient);
        pwd_le->setObjectName(QString::fromUtf8("pwd_le"));
        pwd_le->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(pwd_le, 1, 1, 1, 1);

        login_pb = new QPushButton(TcpClient);
        login_pb->setObjectName(QString::fromUtf8("login_pb"));

        gridLayout->addWidget(login_pb, 2, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        regist_pb = new QPushButton(TcpClient);
        regist_pb->setObjectName(QString::fromUtf8("regist_pb"));
        QFont font1;
        font1.setPointSize(20);
        regist_pb->setFont(font1);

        horizontalLayout->addWidget(regist_pb);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel_pb = new QPushButton(TcpClient);
        cancel_pb->setObjectName(QString::fromUtf8("cancel_pb"));
        cancel_pb->setFont(font1);

        horizontalLayout->addWidget(cancel_pb);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(199, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 177, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QWidget *TcpClient)
    {
        TcpClient->setWindowTitle(QCoreApplication::translate("TcpClient", "TcpClient", nullptr));
        name_lab->setText(QCoreApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215:", nullptr));
        pwd_lab->setText(QCoreApplication::translate("TcpClient", "\345\257\206    \347\240\201:", nullptr));
        login_pb->setText(QCoreApplication::translate("TcpClient", "\347\231\273\345\275\225", nullptr));
        regist_pb->setText(QCoreApplication::translate("TcpClient", "\346\263\250\345\206\214", nullptr));
        cancel_pb->setText(QCoreApplication::translate("TcpClient", "\346\263\250\351\224\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
