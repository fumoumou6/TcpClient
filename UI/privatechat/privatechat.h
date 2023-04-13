#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QWidget>
#include "func/protocol.h"

namespace Ui {
class PrivateChat;
}

class PrivateChat : public QWidget
{
    Q_OBJECT

public:
    explicit PrivateChat(QWidget *parent = nullptr);
    ~PrivateChat();

    static PrivateChat &getInstance();

    void setChatName(QString strName);
    void updateMsg(const PDU *pdu);

public slots:
    void on_sendMsg_pb_clicked();
private:
    Ui::PrivateChat *ui;
    QString m_strChatName;
    QString m_strLoginName;
};

#endif // PRIVATECHAT_H
