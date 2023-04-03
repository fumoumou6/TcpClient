//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_FRIEND_H
#define TCPCLIENT_FRIEND_H

#include <QWidget>
#include "QTextEdit"
#include "QListWidget"
#include "QLineEdit"
#include "QPushButton"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QDebug"
#include "../online/Online.h"

class Friend : public QWidget {
Q_OBJECT

public:
    explicit Friend(QWidget *parent = nullptr);

public slots:
    void showOnline();
private:
    QTextEdit *m_pShowMsgTE;
    QListWidget *m_FriendListWidget;
    QLineEdit *m_pInputMsgLE;

    QPushButton *m_pDelFriendPB;
    QPushButton *m_pFlushFriendPB;
    QPushButton *m_pShowOnlineUsrPB;
    QPushButton *m_pSearchUsrPB;
    QPushButton *m_pMsgSendPB;
    QPushButton *m_pPrivateChatPB;

    Online *m_pOnline;
};


#endif //TCPCLIENT_FRIEND_H
