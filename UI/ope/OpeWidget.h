//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_OPEWIDGET_H
#define TCPCLIENT_OPEWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "QListWidget"
#include "../friend/friend.h"
#include "../book/book.h"

class OpeWidget : public QWidget {
Q_OBJECT

public:
    explicit OpeWidget(QWidget *parent = nullptr);
    static OpeWidget &getInstance();
    Friend *getFriend();

signals:

public slots:


private:
    QListWidget *m_pListW;
    Friend *m_pFriend;
    Book *m_pBook;

    QStackedWidget *m_pSW;
};


#endif //TCPCLIENT_OPEWIDGET_H
