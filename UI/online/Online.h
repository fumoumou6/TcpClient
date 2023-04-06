//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_ONLINE_H
#define TCPCLIENT_ONLINE_H

#include <QWidget>
#include "func/protocol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Online; }
QT_END_NAMESPACE

class Online : public QWidget {
Q_OBJECT

public:
    explicit Online(QWidget *parent = nullptr);

    ~Online() override;

    void showUsr(PDU *pdu);

private:
    Ui::Online *ui;
};


#endif //TCPCLIENT_ONLINE_H
