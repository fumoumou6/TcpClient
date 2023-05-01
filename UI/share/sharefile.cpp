//
// Created by fumoumou on 23-5-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_sharefile.h" resolved

#include "sharefile.h"
#include "../login/tcpclient.h"
#include "../ope/OpeWidget.h"
#include "../../func/protocol.h"
sharefile::sharefile(QWidget *parent) {
     m_pSelectAllPB = new QPushButton("全选");
     m_pCancelSelectPB = new QPushButton("取消全选");

     m_pOKPB = new QPushButton("确定");
     m_pCancelPB = new QPushButton("取消");

     m_pSA = new QScrollArea;
     m_pFriendW = new QWidget;
     m_pFriendWVBL = new QVBoxLayout(m_pFriendW);
     m_pButtonGroup = new QButtonGroup(m_pFriendW);
     m_pButtonGroup->setExclusive(false);   /*设置好友可以多选*/

     QHBoxLayout *pTopHBL = new QHBoxLayout;
     pTopHBL->addWidget(m_pSelectAllPB);
     pTopHBL->addWidget(m_pCancelSelectPB);
     pTopHBL->addStretch();

     QHBoxLayout *pDownHBL = new QHBoxLayout;
     pDownHBL->addWidget(m_pOKPB);
     pDownHBL->addWidget(m_pCancelPB);

     QVBoxLayout *pMainVBL = new QVBoxLayout;
     pMainVBL->addLayout(pTopHBL);
     pMainVBL->addWidget(m_pSA);
     pMainVBL->addLayout(pDownHBL);

    setLayout(pMainVBL);

    connect(m_pCancelSelectPB, SIGNAL(clicked(bool)),
            this, SLOT(cancelSelect()));
    connect(m_pSelectAllPB, SIGNAL(clicked(bool)),
            this, SLOT(selectALl()));

    connect(m_pOKPB, SIGNAL(clicked(bool)),
            this, SLOT(okShare()));
    connect(m_pCancelPB, SIGNAL(clicked(bool)),
            this, SLOT(cancelShare()));
}

sharefile &sharefile::getInstance() {
    qDebug() << "获取sharefile的instance";
    static sharefile instance;
    return instance;
}

void sharefile::updateFriend(QListWidget *pFriendList) {
    qDebug() << "sharefile::updateFriend";
    if (NULL == pFriendList)                                                 /*判空*/
    {
        return;
    }
    QAbstractButton *tmp = NULL;
    QList<QAbstractButton*> preFriendList = m_pButtonGroup->buttons();      /*清空以前的*/
    for (int i = 0; i < preFriendList.size(); ++i) {
        tmp = preFriendList[i];
        m_pFriendWVBL->removeWidget(preFriendList[i]);
        m_pButtonGroup->removeButton(preFriendList[i]);
        preFriendList.removeOne(tmp);
        free(tmp);
        tmp = NULL;
    }
    QCheckBox *pCB = NULL;                                                   /*添加新内容*/
    for (int i = 0; i < pFriendList->count(); ++i) {
        pCB = new QCheckBox(pFriendList->item(i)->text());
        m_pFriendWVBL->addWidget(pCB);
        m_pButtonGroup->addButton(pCB);
    }
    m_pSA->setWidget(m_pFriendW);
}

void sharefile::cancelSelect() {
    QList<QAbstractButton*> cbList = m_pButtonGroup->buttons();
    for (int i = 0; i < cbList.size(); ++i) {
        if (cbList[i]->isChecked())
        {
            cbList[i]->setChecked(false);
        }
    }
}

void sharefile::selectALl() {
    QList<QAbstractButton*> cbList = m_pButtonGroup->buttons();
    for (int i = 0; i < cbList.count(); ++i) {
        if (!cbList[i]->isChecked())
        {
            cbList[i]->setChecked(true);
        }
    }
}

void sharefile::okShare() {
    QString strName = TcpClient::getInstance().loginName();
    QString strCurPath = TcpClient::getInstance().curPath();
    QString strShareFileName = OpeWidget::getInstance().getBook()->getShareFileName();

    QString strPath = strCurPath + "/" + strShareFileName;
    qDebug() << "strPath" << strPath;
    qDebug() << "strCurPath" << strCurPath;
    qDebug() << "strShareFileName" << strShareFileName;

    int num = 0;
    QList<QAbstractButton*> cbList = m_pButtonGroup->buttons();
    for (int i = 0; i < cbList.size(); ++i) {
        if (cbList[i]->isChecked())
        {
            num++;
        }
    }
    PDU *pdu = mkPDU(32*num+strPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_REQUEST;
    sprintf(pdu->caData,"%s %d",strName.toStdString().c_str(),num);
    int j = 0;
    for (int i = 0; i < cbList.count(); ++i) {
        if (cbList[i]->isChecked()){
            memcpy((char *)(pdu->caMsg)+j*32,cbList[i]->text().toStdString().c_str(),cbList[i]->text().size());
            j++;
        }
    }
    memcpy((char *)(pdu->caMsg)+num*32,strPath.toStdString().c_str(),strPath.size());
    TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu =NULL;

}

void sharefile::cancelShare() {

}
