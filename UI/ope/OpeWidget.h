//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_OPEWIDGET_H
#define TCPCLIENT_OPEWIDGET_H

#include <QWidget>
#include "QListWidget"

QT_BEGIN_NAMESPACE
namespace Ui { class OpeWidget; }
QT_END_NAMESPACE

class OpeWidget : public QWidget {
Q_OBJECT

public:
    explicit OpeWidget(QWidget *parent = nullptr);

    ~OpeWidget() override;

private:
    Ui::OpeWidget *ui;
    QListWidget *m_pListW;
};


#endif //TCPCLIENT_OPEWIDGET_H
