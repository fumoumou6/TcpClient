//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_FRIEND_H
#define TCPCLIENT_FRIEND_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class friend; }
QT_END_NAMESPACE

class friend

: public QWidget {
Q_OBJECT

public:
explicit friend(
QWidget *parent = nullptr
);
~friend()
override;

private:
Ui:: friend *ui;
};


#endif //TCPCLIENT_FRIEND_H
