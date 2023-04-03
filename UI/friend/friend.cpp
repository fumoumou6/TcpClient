//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Friend.h" resolved

#include "friend.h"


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
    connect(m_pShowOnlineUsrPB, SIGNAL(clicked(bool)), this, SLOT(showOnline()));
}

void Friend::showOnline() {
    qDebug() << "显示在线用户";
    if (m_pOnline->isHidden()){
        m_pOnline->show();
    } else{
        m_pOnline->hide();
    }
}
