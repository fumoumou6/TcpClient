//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Online.h" resolved

#include "Online.h"
#include "ui_Online.h"
#include "../UI/login/tcpclient.h"

Online::Online(QWidget *parent) :
        QWidget(parent), ui(new Ui::Online) {
    ui->setupUi(this);
}

Online::~Online() {
    delete ui;
}

void Online::showUsr(PDU *pdu) {
    if (NULL == pdu){
        return;
    }
    uint uiSize = pdu->uiMsgLen/32;
    char caTmp[32];
    ui->online_lw->clear();
    for (uint i = 0; i < uiSize; ++i) {
        memcpy(caTmp,(char *)(pdu->caMsg)+i*32,32);
//        Ui_->online_lw->addItem(caTmp);
              /*先清理再显示防止重复显示*/
            ui->online_lw->addItem(caTmp);
    }
}

void Online::on_adduser_pb_clicked(){
    qDebug() << "加好友按键点击";
    QListWidgetItem *pItem = ui->online_lw->currentItem();
    qDebug() << pItem->text();
    QString strPerUseName = pItem->text();
    QString strLoginName = TcpClient::getInstance().loginName();
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REQUEST;
    memcpy(pdu->caData,strPerUseName.toStdString().c_str(),strPerUseName.size());
    memcpy(pdu->caData+32,strLoginName.toStdString().c_str(),strLoginName.size());
    TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}