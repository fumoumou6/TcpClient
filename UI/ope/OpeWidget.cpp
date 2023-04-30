//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OpeWidget.h" resolved

#include "OpeWidget.h"


OpeWidget::OpeWidget(QWidget *parent) : QWidget(parent){

    m_pListW = new QListWidget(this);
    m_pListW->addItem("好友");
    m_pListW->addItem("图书");

    m_pFriend = new Friend;
    m_pBook = new Book;

    m_pSW = new QStackedWidget;
    m_pSW->addWidget(m_pFriend);
    m_pSW->addWidget(m_pBook);

    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addWidget(m_pListW);
    pMain->addWidget(m_pSW);
    setLayout(pMain);
    connect(m_pListW, SIGNAL(currentRowChanged(int)),
            m_pSW, SLOT(setCurrentIndex(int)));
}

OpeWidget &OpeWidget::getInstance() {
    qDebug() << "获取OpeWidget";
    static OpeWidget instance;
    return instance;
}

Friend *OpeWidget::getFriend() {
    qDebug() << "获取OpeWidget:firend";
    return m_pFriend;
}

Book *OpeWidget::getBook() {
    qDebug() << "获取OpeWidget: book";
    return m_pBook;
}

