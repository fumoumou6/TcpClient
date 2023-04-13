//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Friend.h" resolved

#include "friend.h"
#include "./func/protocol.h"
#include "./UI/login/tcpclient.h"
#include "QInputDialog"
#include "UI/privatechat/privatechat.h"

Friend::Friend(QWidget *parent) : QWidget(parent){
    m_pShowMsgTE = new QTextEdit;
    m_FriendListWidget = new QListWidget;
    m_pInputMsgLE = new QLineEdit;

    m_pDelFriendPB  = new QPushButton("删除好友");
    m_pFlushFriendPB = new QPushButton("刷新好友");
    m_pShowOnlineUsrPB = new QPushButton("显示在线用户");
    m_pSearchUsrPB = new QPushButton("查找用户");

    m_pMsgSendPB = new QPushButton("发送信息");
    m_pPrivateChatPB = new QPushButton("私聊");

    QVBoxLayout *pRightPBVL = new QVBoxLayout;   /*垂直布局按键*/
    pRightPBVL->addWidget(m_pDelFriendPB);
    pRightPBVL->addWidget(m_pFlushFriendPB);
    pRightPBVL->addWidget(m_pShowOnlineUsrPB);
    pRightPBVL->addWidget(m_pSearchUsrPB);
    pRightPBVL->addWidget(m_pPrivateChatPB);

    QHBoxLayout *pTopHBL = new QHBoxLayout;   /*水平布局好友和消息列表*/
    pTopHBL->addWidget(m_pShowMsgTE);
    pTopHBL->addWidget(m_FriendListWidget);
    pTopHBL->addLayout(pRightPBVL);

    QHBoxLayout *pMsgHBL = new QHBoxLayout;  /*水平布局输入框 发送按键*/
    pMsgHBL->addWidget(m_pInputMsgLE);
    pMsgHBL->addWidget(m_pMsgSendPB);

    m_pOnline = new Online;

    QVBoxLayout *pMain = new QVBoxLayout;   /*垂直布局上半部分和聊天部分*/
    pMain->addLayout(pTopHBL);
    pMain->addLayout(pMsgHBL);
    pMain->addWidget(m_pOnline);           /*在线用户窗口*/
    m_pOnline->hide();


    setLayout(pMain);                       /*设置界面*/

    /*连接显示在线用户按键的信号*/
    connect(m_pShowOnlineUsrPB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(showOnline()));
    connect(m_pSearchUsrPB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(searchUsr()));
    connect(m_pFlushFriendPB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(flushFriend()));
    connect(m_pDelFriendPB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(delFriend()));
    connect(m_pPrivateChatPB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(privateChat()));
}

void Friend::showOnline() {
    qDebug() << "显示在线用户";
    if (m_pOnline->isHidden()){
        m_pOnline->show();
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINE_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;

    } else{
        m_pOnline->hide();
    }
}

void Friend::showAllOnlineUsr(PDU *pdu) {
    if (NULL ==pdu){
        return;
    }
    m_pOnline->showUsr(pdu);
}

void Friend::searchUsr() {
    qDebug() << "查找用户";
    m_strSEarchName = QInputDialog::getText(this,"搜索","用户名:");
    if (!m_strSEarchName.isEmpty()){
        qDebug() << m_strSEarchName;
        PDU *pdu = mkPDU(0);
        memcpy(pdu->caData,m_strSEarchName.toStdString().c_str(),m_strSEarchName.size());
        pdu->uiMsgType = ENUM_MSG_TYPE_SERACH_USR_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }

}

void Friend::flushFriend() {
    qDebug() << "刷新好友";
    QString strName = TcpClient::getInstance().loginName();
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST;
    memcpy(pdu->caData,strName.toStdString().c_str(),strName.size());
    TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;

}

void Friend::updateFriendList(PDU *pdu) {
    if (NULL == pdu){
        return;
    }
    uint uiSize = pdu->uiMsgLen/32;
    char caName[32] = {'\0'};
    m_FriendListWidget->clear();
    for (int i = 0; i < uiSize; ++i) {
        memcpy(caName,(char *)(pdu->caMsg)+i*32,32);
        m_FriendListWidget->addItem(caName);

    }
}

void Friend::delFriend() {
    if(NULL != m_FriendListWidget->currentItem()){
        QString strFriendName = m_FriendListWidget->currentItem()->text();
        qDebug() << strFriendName;
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST;
        QString strSelfName = TcpClient::getInstance().loginName();
        memcpy(pdu->caData,strSelfName.toStdString().c_str(),strSelfName.size());
        memcpy(pdu->caData+32,strFriendName.toStdString().c_str(),strFriendName.size());
        TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
        free(pdu);
        pdu =NULL;

    } else{
        QMessageBox::warning(this,"警告","先选中好友");
    }

}

void Friend::privateChat() {
    qDebug() << "私聊按键点击";
    if (NULL != m_FriendListWidget->currentItem()){
        QString strChatName = m_FriendListWidget->currentItem()->text();
        PrivateChat::getInstance().setChatName(strChatName);
        if (PrivateChat::getInstance().isHidden()){
            PrivateChat::getInstance().show();
        }

    } else{
        QMessageBox::warning(this,"私聊","请选择私聊对象");

    }
}
