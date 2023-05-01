//
// Created by fumoumou on 23-5-1.
//

#ifndef TCPCLIENT_SHAREFILE_H
#define TCPCLIENT_SHAREFILE_H

#include <QWidget>
#include <QListWidget>
#include "QPushButton"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QButtonGroup"
#include "QScrollArea"
#include "QCheckBox"
#include "QDebug"
class sharefile : public QWidget {
Q_OBJECT

public:
    explicit sharefile(QWidget *parent = 0);
    static sharefile &getInstance();
    void updateFriend(QListWidget *pFriendList);
public slots:
    void cancelSelect();
    void selectALl();

    void okShare();
    void cancelShare();

private:
    QPushButton *m_pSelectAllPB;
    QPushButton *m_pCancelSelectPB;

    QPushButton *m_pOKPB;
    QPushButton *m_pCancelPB;

    QScrollArea *m_pSA;
    QWidget *m_pFriendW;
    QVBoxLayout *m_pFriendWVBL;
    QButtonGroup *m_pButtonGroup;

};


#endif //TCPCLIENT_SHAREFILE_H
