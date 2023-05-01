//
// Created by fumoumou on 23-3-31.
//


#include "book.h"
#include "../login/tcpclient.h"
#include "QInputDialog"
#include "QMessageBox"
#include "QFileDialog"
#include "../share/sharefile.h"

Book::Book(QWidget *parent) : QWidget(parent){

    m_strEnterDir.clear();
    m_bDownload = false;

    m_pTimer = new QTimer;

    m_pBookListW = new QListWidget;

     m_pReturnPB = new QPushButton("返回");
     m_pCreateDirPB = new QPushButton("创建文件夹");
     m_pDelDirPB = new QPushButton("删除文件夹");
     m_pRenamePB = new QPushButton("重命名文件");
     m_pFlushFilePB = new QPushButton("刷新文件");

    QVBoxLayout *pDirVBL = new QVBoxLayout;
     pDirVBL->addWidget(m_pReturnPB);
     pDirVBL->addWidget(m_pCreateDirPB);
     pDirVBL->addWidget(m_pDelDirPB);
     pDirVBL->addWidget(m_pRenamePB);
     pDirVBL->addWidget(m_pFlushFilePB);

     m_pUploadPB = new QPushButton("上传文件");
     m_pDownloadPB = new QPushButton("下载文件");
     m_pDelFilePB = new QPushButton("删除文件");
     m_pShareFilePB = new QPushButton("共享文件");

    QVBoxLayout *pFileVBL = new QVBoxLayout;
    pFileVBL->addWidget(m_pUploadPB);
    pFileVBL->addWidget(m_pDownloadPB);
    pFileVBL->addWidget(m_pDelFilePB);
    pFileVBL->addWidget(m_pShareFilePB);

    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addWidget(m_pBookListW);
    pMain->addLayout(pDirVBL);
    pMain->addLayout(pFileVBL);

    setLayout(pMain);

    connect(m_pCreateDirPB, SIGNAL(clicked(bool)),
            this, SLOT(createDir()));
    connect(m_pFlushFilePB, SIGNAL(clicked(bool)),
            this, SLOT(flushFile()));
    connect(m_pDelDirPB, SIGNAL(clicked(bool)),
            this, SLOT(delDir()));
    connect(m_pRenamePB, SIGNAL(clicked(bool)),
            this, SLOT(renameFile()));
    connect(m_pBookListW, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(enterDir(QModelIndex)));
    connect(m_pReturnPB, SIGNAL(clicked(bool)),
            this, SLOT(returnPre()));
    connect(m_pUploadPB, SIGNAL(clicked(bool)),
            this, SLOT(uploadFile()));
    connect(m_pTimer, SIGNAL(timeout()),
            this, SLOT(uploadFileData()));
    connect(m_pDelFilePB, SIGNAL(clicked(bool)),
            this, SLOT(delRegFile()));
    connect(m_pDownloadPB, SIGNAL(clicked(bool)),
            this, SLOT(downloadFile()));
    connect(m_pShareFilePB, SIGNAL(clicked(bool)),
            this, SLOT(shareFile()));
}

void Book::createDir() {
    QString strNewDir = QInputDialog::getText(this,"新建文件夹","新文件夹名字");
    if (!strNewDir.isEmpty()){
        if (strNewDir.size()>32){
            QMessageBox::warning(this,"新建文件夹","新文件夹名字不能超过32个字符");
        } else{
            QString strName = TcpClient::getInstance().loginName();
            QString strCurPath = TcpClient::getInstance().curPath();
            PDU *pdu = mkPDU(strCurPath.size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_REQUEST;
            strncpy(pdu->caData,strName.toStdString().c_str(), strName.size());
            strncpy(pdu->caData+32,strNewDir.toStdString().c_str(), strNewDir.size());

            memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());

            TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
            free(pdu);
            pdu = NULL;
        }

    }else{
        QMessageBox::warning(this,"新建文件夹","新文件夹名字不能为空");
    }

}

void Book::flushFile() {
    /*刷新文件列表*/
    qDebug() << "刷新文件列表";
    QString strCurPath = TcpClient::getInstance().curPath();
    PDU *pdu = mkPDU(strCurPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FILE_REQUEST;
    strncpy((char *)(pdu->caMsg),strCurPath.toStdString().c_str(),strCurPath.size());
    TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::updateFileListList(const PDU *pdu) {
    qDebug() << "更新文件列表";
    if (NULL == pdu)
    {
        qDebug() << "更新文件列表获取pdu失败";
        return;
    }
    m_pBookListW->clear();
    qDebug() << "清理文件列表";
    FileInfo *pFileInfo = NULL;
    int iCount = pdu->uiMsgLen/sizeof(FileInfo);
    for (int i = 0; i < iCount; ++i) {
        pFileInfo = (FileInfo*)(pdu->caMsg)+i;
        qDebug() << pFileInfo->caFileName << pFileInfo->iFileTYpe;
        QListWidgetItem *pItem = new QListWidgetItem;

        /*不会添加ｑｒｃ文件　直接使用的绝对路径*/
        if (0 == pFileInfo->iFileTYpe){

            pItem->setIcon(QIcon(QPixmap("/home/fumoumou/Desktop/NetDisk/TcpClient/resource/map/dir.jpg")));

        } else if(1 == pFileInfo->iFileTYpe)
        {
            pItem->setIcon(QIcon(QPixmap("/home/fumoumou/Desktop/NetDisk/TcpClient/resource/map/reg.jpg")));
        }
        pItem->setText(pFileInfo->caFileName);
        m_pBookListW->addItem(pItem);
    }

}

void Book::delDir() {
    QString strCurPath = TcpClient::getInstance().curPath();
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if (NULL == pItem)
    {
        QMessageBox::warning(this,"删除文件","请选择要删除的文件");
    } else{
        QString strDelName = pItem->text();
        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_DEL_DIR_REQUEST;
        strncpy(pdu->caData,strDelName.toStdString().c_str(),strDelName.size());
        memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());

        TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Book::renameFile() {
    QString strCurPath = TcpClient::getInstance().curPath();
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if (NULL == pItem)
    {
        QMessageBox::warning(this,"重命名文件","请选择要重命名的文件");
    } else{
        QString strOldName = pItem->text();
        QString strNewName = QInputDialog::getText(this,"重命名文件","请输入新的文件名");
        if (!strNewName.isEmpty())
        {
            PDU *pdu = mkPDU(strCurPath.size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_RENAME_FILE_REQUEST;
            strncpy(pdu->caData,strOldName.toStdString().c_str(),strOldName.size());
            strncpy(pdu->caData+32,strNewName.toStdString().c_str(),strNewName.size());
            memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());

            TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
            free(pdu);
            pdu = NULL;
        } else
        {
            QMessageBox::warning(this,"重命名文件","新文件名不能为空");
        }
    }
}

void Book::enterDir(const QModelIndex &index) {
//    qDebug() << "enter dir";
    QString strDirName = index.data().toString();
//    qDebug() << strDirName;
    m_strEnterDir = strDirName; /*保存路径*/

    QString strCurPath = TcpClient::getInstance().curPath();

    PDU *pdu = mkPDU(strCurPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_ENTER_DIR_REQUEST;
    strncpy(pdu->caData,strDirName.toStdString().c_str(),strDirName.size());
    memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());

    TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::clearEnterDir() {
    m_strEnterDir.clear();
}

QString Book::enterDir() {
    return m_strEnterDir;
}

void Book::returnPre() {
    QString strCurPath = TcpClient::getInstance().curPath();
    QString strRootPath = "./" + TcpClient::getInstance().loginName();
    if (strCurPath == strRootPath)
    {
        QMessageBox::warning(this,"返回","返回失败: 已经在顶层目录中");
    } else
    {
        int index = strCurPath.lastIndexOf('/');
        strCurPath.remove(index, strCurPath.size()-index);
        qDebug() << "return -->" << strCurPath;
        TcpClient::getInstance().setCurPath(strCurPath);

        clearEnterDir();
        flushFile();     /*刷新列表*/
    }
}

void Book::uploadFile() {

    m_strUploadFilePath = QFileDialog::getOpenFileName();
    qDebug() << m_strUploadFilePath;
    if (!m_strUploadFilePath.isEmpty())
    {
        int index = m_strUploadFilePath.lastIndexOf('/');
        QString strFileName = m_strUploadFilePath.right(m_strUploadFilePath.size()-index-1);
        qDebug() << strFileName; /*显示文件名*/

        QFile file(m_strUploadFilePath);
        qint64 fileSize = file.size(); /*获得文件大小*/

        QString strCurPath = TcpClient::getInstance().curPath();

        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST;
        memcpy(pdu->caMsg,strCurPath.toStdString().c_str(), strCurPath.size());
        sprintf(pdu->caData,"%s %11d",strFileName.toStdString().c_str(),fileSize);

        qDebug() << "上传文件名" << strFileName;
        TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;

        m_pTimer->start(1000);

    } else
    {
        QMessageBox::warning(this,"上传文件","上传文件名称不能为空");
    }
}

void Book::uploadFileData() {
    m_pTimer->stop();
    QFile file(m_strUploadFilePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"上传文件","打开文件失败");
        return;
    }
    char *pBuffer = new char[4096];
    qint64 ret = 0;
    while (true)
    {
        ret = file.read(pBuffer,4096);
        if (ret > 0 && ret <= 4096)
        {
            TcpClient::getInstance().getTcpSocket().write(pBuffer,ret);
        } else if (0 == ret)
        {
            break;
        } else
        {
            QMessageBox::warning(this,"上传文件","上传文件失败：读文件失败");
            break;
        }
    }
    file.close();
    delete[] pBuffer;

    pBuffer = NULL;
}

void Book::delRegFile() {
    QString strCurPath = TcpClient::getInstance().curPath();
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if (NULL == pItem)
    {
        QMessageBox::warning(this,"删除文件","请选择要删除的文件");
    } else{
        QString strDelName = pItem->text();
        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_DEL_FILE_REQUEST;
        strncpy(pdu->caData,strDelName.toStdString().c_str(),strDelName.size());
        memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());

        TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Book::downloadFile() {
    qDebug() << "下载文件请求";
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if (NULL == pItem)
    {
        QMessageBox::warning(this,"下载文件","请选择要下载的文件");
    } else{

        QString strSaveFilePath = QFileDialog::getSaveFileName();
        if (strSaveFilePath.isEmpty())
        {
            QMessageBox::warning(this,"下载文件","请指定要下载的位置");
            m_strSaveFilePath.clear();
        } else
        {
            m_strSaveFilePath = strSaveFilePath;
        }

        QString strCurPath = TcpClient::getInstance().curPath();

        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST;
        QString strFileName = pItem->text();
        strncpy(pdu->caData,strFileName.toStdString().c_str(),strFileName.size());
        memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());

        TcpClient::getInstance().getTcpSocket().write((char *)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;


    }
}

void Book::setDownloadStatus(bool status) {
    qDebug() << "setDownloadStatus: " << status;
    m_bDownload =status;
}

bool Book::getDownloadStatus() {
    qDebug() << "getDownloadStatus: " << m_bDownload;
    return m_bDownload;
}

QString Book::getSaveFilePath() {
    qDebug() << "getSaveFilePath: " << m_strSaveFilePath;
    return m_strSaveFilePath;
}

void Book::shareFile() {
    qDebug() << "分享文件";

    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if (NULL == pItem)
    {
        QMessageBox::warning(this,"分享文件","请选择要分享的文件");
        return;
    } else{
        m_strShareFileName = pItem->text();
    }
    Friend *pFriend = OpeWidget::getInstance().getFriend();
    QListWidget *pFriendList = pFriend->getFriendLIst();
    sharefile::getInstance().updateFriend(pFriendList);
    if (sharefile::getInstance().isHidden())
    {
        sharefile::getInstance().show();
    }
}

QString Book::getShareFileName() {
    qDebug() << "BOOK:m_strShareFileName";
    return m_strShareFileName;
}

