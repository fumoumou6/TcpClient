#include "tcpclient.h"
#include "./ui_tcpclient.h"
#include "func/protocol.h"
#include "UI/privatechat/privatechat.h"

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
    if (!OpeWidget::getInstance().getBook()->getDownloadStatus()) {
        uint uiPDULen = 0;

        m_tcpSocket.read((char *) &uiPDULen, sizeof(uint));
        uint uiMsgLen = uiPDULen - sizeof(PDU);
        PDU *pdu = mkPDU(uiMsgLen);                                        /*接收的pdu*/
        m_tcpSocket.read((char *) pdu + sizeof(uint), uiPDULen);


        switch (pdu->uiMsgType) {
            case ENUM_MSG_TYPE_REGIST_RESPOND: {
                if (0 == strcmp(pdu->caData, REGIST_OK)) {
                    QMessageBox::information(this, "注册", REGIST_OK);

                } else if (0 == strcmp(pdu->caData, REGIST_FAILED)) {
                    QMessageBox::warning(this, "注册", REGIST_FAILED);
                }
                break;
            }
            case ENUM_MSG_TYPE_LOGIN_RESPOND: {
                if (0 == strcmp(pdu->caData, LOGIN_OK)) {

                    m_strCurPath = QString("./%1").arg(m_strLoginName);

                    QMessageBox::information(this, "登录", LOGIN_OK);

                    /*登录成功显示主界面*/
                    OpeWidget::getInstance().show();
                    this->hide();

                } else if (0 == strcmp(pdu->caData, LOGIN_FAILED)) {
                    QMessageBox::warning(this, "登录", LOGIN_FAILED);
                }
                break;
            }
            case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND: {
                OpeWidget::getInstance().getFriend()->showAllOnlineUsr(pdu);
                break;
            }
            case ENUM_MSG_TYPE_SERACH_USR_RESPOND: {
                if (0 == strcmp(SEARCH_USR_NO, pdu->caData)) {
                    QMessageBox::information(this,
                                             "搜索",
                                             QString("%1: not exist").arg(
                                                     OpeWidget::getInstance().getFriend()->m_strSEarchName));
                } else if (0 == strcmp(SEARCH_USR_ONLINE, pdu->caData)) {
                    QMessageBox::information(this,
                                             "搜索",
                                             QString("%1: online").arg(
                                                     OpeWidget::getInstance().getFriend()->m_strSEarchName));
                } else if (0 == strcmp(SEARCH_USR_OFFLINE, pdu->caData)) {
                    QMessageBox::information(this,
                                             "搜索",
                                             QString("%1: offline").arg(
                                                     OpeWidget::getInstance().getFriend()->m_strSEarchName));
                }
                break;
            }
            case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST: {
                qDebug() << "回复：加好友回复";

                char caName[32] = {'\0'};;
                strncpy(caName, pdu->caData + 32, 32);
                int ret = QMessageBox::information(this, "添加好友",
                                                   QString("%1 wanto add friend").arg(caName),
                                                   QMessageBox::Yes, QMessageBox::No);

                PDU *respdu = mkPDU(0);

                memcpy(respdu->caData, pdu->caData, 64);

                if (QMessageBox::Yes == ret) {

                    respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE;
                    qDebug() << "同意加好友";
                } else {

                    respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REFUSE;
                    qDebug() << "拒绝加好友";
                    break;
                }
                m_tcpSocket.write((char *) respdu, respdu->uiPDULen);
                qDebug() << "perName" << pdu->caData + 32 << "name" << pdu->caData;
                free(respdu);
                respdu = NULL;

                break;
            }
            case ENUM_MSG_TYPE_ADD_FRIEND_RESPOND: {


                qDebug() << "回复：加好友请求";
                qDebug() << pdu->caData;
                if (0 == strcmp(UNKNOW_ERROR, pdu->caData)) {
                    QMessageBox::information(this,
                                             "加好友",
                                             "好友不存在");
                } else if (0 == strcmp(EXISTED_FRIEND, pdu->caData)) {
                    QMessageBox::information(this,
                                             "加好友",
                                             "好友已存在");
                } else if (0 == strcmp(ADD_FRIEND_OFFLINE, pdu->caData)) {
                    QMessageBox::information(this,
                                             "加好友",
                                             "好友不在线");
                } else if (0 == strcmp(ADD_FRIEND_NOEXIST, pdu->caData)) {
                    QMessageBox::information(this,
                                             "加好友",
                                             "用户不存在");
                }
                break;

            }
            case ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND: {
                OpeWidget::getInstance().getFriend()->updateFriendList(pdu);

                break;
            }
            case ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST: {
                char caName[32] = {'\0'};
                memcpy(caName, pdu->caData, 32);
                QMessageBox::information(this, "删除好友", QString("%1 删除你作为他好友").arg(caName));
                break;
            }
            case ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND: {
                QMessageBox::information(this, "删除好友", "删除好友成功");
                break;
            }
            case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST: {
                if (PrivateChat::getInstance().isHidden()) {

                    PrivateChat::getInstance().show();
                }
                char caSendName[32] = {'\0'};
                memcpy(caSendName, pdu->caData, 32);
                QString strSendName = caSendName;
                PrivateChat::getInstance().setChatName(strSendName);
                PrivateChat::getInstance().updateMsg(pdu);
                break;
            }
            case ENUM_MSG_TYPE_GROUP_CHAT_REQUEST: {
                qDebug() << "收到群聊消息";
                OpeWidget::getInstance().getFriend()->updateGroupMsg(pdu);

                break;
            }
            case ENUM_MSG_TYPE_CREATE_DIR_RESPOND: {
                QMessageBox::information(this, "创建文件夹", pdu->caData);
                break;
            }
            case ENUM_MSG_TYPE_FLUSH_FILE_RESPOND: {
                qDebug() << "ENUM_MSG_TYPE_FLUSH_FILE_RESPOND";
                qDebug() << "pdu大小" << sizeof(pdu);

                OpeWidget::getInstance().getBook()->updateFileListList(pdu);
                QString strEnterDir = OpeWidget::getInstance().getBook()->enterDir();
                qDebug() << strEnterDir;
                if (!strEnterDir.isEmpty()) {
                    m_strCurPath = m_strCurPath + '/' + strEnterDir;
                    qDebug() << "Enter Dir :" << m_strCurPath;
                }
                break;
            }
            case ENUM_MSG_TYPE_DEL_DIR_RESPOND: {
                QMessageBox::information(this, "删除文件夹", pdu->caData);
                break;

            }
            case ENUM_MSG_TYPE_RENAME_FILE_RESPOND: {
                QMessageBox::information(this, "重命名文件", pdu->caData);
                break;
            }
            case ENUM_MSG_TYPE_ENTER_DIR_RESPOND: {
                QMessageBox::information(this, "进入文件夹", pdu->caData);
                OpeWidget::getInstance().getBook()->clearEnterDir();
                break;
            }
            case ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND: {
                QMessageBox::information(this, "上传文件", pdu->caData);
                break;
            }
            case ENUM_MSG_TYPE_DEL_FILE_RESPOND: {
                QMessageBox::information(this, "删除文件", pdu->caData);
                break;
            }
            case ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND: {
                qDebug() << "下载文件回复";
                qDebug() << pdu->caData;
                char caFileName[32] = {'\0'};
                sscanf(pdu->caData, "%s %11d", caFileName, &(OpeWidget::getInstance().getBook()->m_iTotal));
                qDebug() << pdu->caData;
                if (strlen(caFileName) > 0 && OpeWidget::getInstance().getBook()->m_iTotal > 0) {
                    OpeWidget::getInstance().getBook()->setDownloadStatus(true);
                    m_file.setFileName(OpeWidget::getInstance().getBook()->getSaveFilePath());
                    if (!m_file.open(QIODevice::WriteOnly))
                    {
                        QMessageBox::warning(this,"下载文件","获得保存文件的路径失败");
                    }
                    qDebug() << "准备开始下载";
                }


                break;
            }
            case ENUM_MSG_TYPE_SHARE_FILE_RESPOND:{
                QMessageBox::information(this, "共享文件", pdu->caData);
                break;
            }
            case ENUM_MSG_TYPE_SHARE_FILE_NOTE:{
                qDebug() << "ENUM_MSG_TYPE_SHARE_FILE_NOTE";
                char *pPath = new char[pdu->uiMsgLen];
                memcpy(pPath,pdu->caMsg,pdu->uiMsgLen);
                char *pos = strrchr(pPath,'/');
                if (NULL != pos)
                {
                    pos++;
                    QString strNote = QString("%1 share file-> %2 \n Do you accept ?").arg(pdu->caData).arg(pos);
                    int ret = QMessageBox::question(this,"共享文件",strNote);
                    if (QMessageBox::Yes == ret)
                    {
                        PDU *respdu = mkPDU(pdu->uiMsgLen);
                        respdu->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND;
                        memcpy(respdu->caMsg,pdu->caMsg,pdu->uiMsgLen);
                        QString strName = TcpClient::getInstance().loginName();
                        strcpy(respdu->caData,strName.toStdString().c_str());
                        m_tcpSocket.write((char *)respdu,respdu->uiPDULen);

                    }
                }
                break;
            }
            default:
                break;
        }
        free(pdu);
        pdu = NULL;
    } else{
        qDebug() << "接收数据";
        QByteArray buffer = m_tcpSocket.readAll();
        qDebug() << "接收数据完成";
        qDebug() << "m_file位置：" << m_file.fileName();
        m_file.write(buffer);
        qDebug() << "写入文件";
        Book *pBook = OpeWidget::getInstance().getBook();
        pBook->m_iReceived += buffer.size();
        if (pBook->m_iTotal == pBook->m_iReceived)
        {
            m_file.close();
            pBook->m_iTotal = 0;
            pBook->m_iReceived = 0;
            pBook->setDownloadStatus(false);
            qDebug() << "接收数据完成";
        } else if (pBook->m_iTotal < pBook->m_iReceived)
        {
            m_file.close();
            pBook->m_iTotal = 0;
            pBook->m_iReceived = 0;
            pBook->setDownloadStatus(false);

            QMessageBox::critical(this,"下载文件","下载文件失败");
        }
        qDebug() << "接收数据流程结束";
    }
}


void TcpClient::on_login_pb_clicked() {
    qDebug() << "login_pb clicked";
    QString strName = ui->name_le->text();
    QString strPwd = ui->pwd_le->text();
    if (!strName.isEmpty()&& !strPwd.isEmpty()){          /*登录操作*/

        m_strLoginName = strName;   /*保存登录信息*/

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

QString TcpClient::loginName() {
    return m_strLoginName;
}

QString TcpClient::curPath() {
    return m_strCurPath;
}

void TcpClient::setCurPath(QString strCurPath) {
    m_strCurPath = strCurPath;
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
