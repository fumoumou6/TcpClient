//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_BOOK_H
#define TCPCLIENT_BOOK_H

#include <QWidget>
#include "QListWidget"
#include "QPushButton"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "../func/protocol.h"
#include "QTimer"

class Book : public QWidget {
Q_OBJECT

public:
    explicit Book(QWidget *parent = nullptr);
    void updateFileListList(const PDU *pdu);
public slots:
    void createDir();
    void flushFile();
    void delDir();
    void renameFile();
    void enterDir(const QModelIndex &index);
    void clearEnterDir();
    QString enterDir();
    void returnPre();
    void uploadFile();
    void uploadFileData();
private:
    QListWidget *m_pBookListW;
    QPushButton *m_pReturnPB;
    QPushButton *m_pCreateDirPB;
    QPushButton *m_pDelDirPB;
    QPushButton *m_pRenamePB;
    QPushButton *m_pFlushFilePB;
    QPushButton *m_pUploadPB;
    QPushButton *m_pDownloadPB;
    QPushButton *m_pDelFilePB;
    QPushButton *m_pShareFilePB;

    QString m_strEnterDir;
    QString m_strUploadFilePath;
    QTimer *m_pTimer;
};


#endif //TCPCLIENT_BOOK_H
