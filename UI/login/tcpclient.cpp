#include "tcpclient.h"
#include "./ui_tcpclient.h"
#include "func/protocol.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);

//    resize(500,300);     /*重新设置一下界面尺寸*/

    loadConfig();

//    ui->lineEdit->setText("hello");

    connect(&m_tcpSocket, SIGNAL(connected()), this, SLOT(showConnect()));
    connect(&m_tcpSocket, SIGNAL(readyRead()), this, SLOT(recvMsg()));


    m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);
    m_tcpSocket.waitForConnected();  //否则不触发connected信号

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()
{
    QString runPath = QCoreApplication::applicationDirPath() + "/../resource/client.config";
//    qDebug() <<runPath;
    QFile file(runPath);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray bytedata = file.readAll();
        QString strData = bytedata.toStdString().c_str();
//        qDebug() << strData;
        file.close();

        strData.replace("\n"," ");
//        qDebug() << strData;

        QStringList strlist = strData.split(" ");

        m_strIP = strlist.at(0);
        m_usPort = strlist.at(1).toUShort();
//        qDebug() << "ip:" << m_strIP << " port:" << m_usPort;



    } else{

        QMessageBox::critical(this,"open config","open config fail");
    }
}

void TcpClient::showConnect(){
    qDebug("connect server ok");
    QMessageBox::information(this,"连接服务器","连接服务器成功");      /*会阻塞等待 阻止主界面显示 */
//    qDebug() << "STOP";

}
void TcpClient::recvMsg() {              /*收到回复报文*/
    uint uiPDULen = 0;

    m_tcpSocket.read((char *)&uiPDULen,sizeof(uint));
    uint uiMsgLen = uiPDULen-sizeof(PDU);
    PDU *pdu = mkPDU(uiMsgLen);                                        /*接收的pdu*/
    m_tcpSocket.read((char *)pdu+sizeof(uint),uiPDULen);



    switch (pdu->uiMsgType) {
        case ENUM_MSG_TYPE_REGIST_RESPOND:{
            if (0 == strcmp(pdu->caData,REGIST_OK)){
                QMessageBox::information(this,"注册",REGIST_OK);

            } else if (0 == strcmp(pdu->caData,REGIST_FAILED)){
                QMessageBox::warning(this,"注册",REGIST_FAILED);
            }
            break;
        }
        case ENUM_MSG_TYPE_LOGIN_RESPOND:{
            if (0 == strcmp(pdu->caData,LOGIN_OK)){
                QMessageBox::information(this,"登录",LOGIN_OK);

                /*登录成功显示主界面*/
                OpeWidget::getInstance().show();
                this->hide();

            } else if (0 == strcmp(pdu->caData,LOGIN_FAILED)){
                QMessageBox::warning(this,"登录",LOGIN_FAILED);
            }
            break;
        }
        case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND:{
            OpeWidget::getInstance().getFriend()->showAllOnlineUsr(pdu);
            break;
        }

        default:
            break;
    }
    free(pdu);
    pdu = NULL;
}


void TcpClient::on_login_pb_clicked() {
    qDebug() << "login_pb clicked";
    QString strName = ui->name_le->text();
    QString strPwd = ui->pwd_le->text();
    if (!strName.isEmpty()&& !strPwd.isEmpty()){          /*登录操作*/

        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_REQUEST;
        strncpy(pdu->caData,strName.toStdString().c_str(),32);
        strncpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;


    } else{
        QMessageBox::warning(this,"登录","登录失败：帐号和密码不能为空");
    }

}

void TcpClient::on_regist_pb_clicked() {
    qDebug() << "regist_pb clicked";
    QString strName = ui->name_le->text();
    QString strPwd = ui->pwd_le->text();
    if (!strName.isEmpty()&& !strPwd.isEmpty()){
//        QMessageBox::warning(this,"注册","注册成功");
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUDEST;
        strncpy(pdu->caData,strName.toStdString().c_str(),32);
        strncpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    } else{
        QMessageBox::warning(this,"注册","注册失败：帐号和密码不能为空");
    }
}

void TcpClient::on_cancel_pb_clicked() {
    qDebug() << "cancel_pb clicked";
}

TcpClient &TcpClient::getInstance() {
    static TcpClient instance;
    return instance;
}

QTcpSocket &TcpClient::getTcpSocket() {
    return m_tcpSocket;
}



/*void TcpClient::on_send_pb_clicked()
{
    QString strMsg = ui->lineEdit->text();
    if (!strMsg.isEmpty()){
        PDU *pdu =mkPDU(strMsg.size());
        pdu->uiMsgType = 8888;
        memcpy(pdu->caMsg,strMsg.toStdString().c_str(),strMsg.size());
        qDebug() << (char *)(pdu->caMsg);
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
        qDebug() << "发送完成";
        free(pdu);
        pdu = NULL;


    } else{
                QMessageBox::warning(this,"信息发送","发送信息部不能为空");
    }
}*/
