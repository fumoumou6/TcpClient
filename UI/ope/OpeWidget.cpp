//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OpeWidget.h" resolved

#include "OpeWidget.h"
#include "ui_OpeWidget.h"


OpeWidget::OpeWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::OpeWidget) {
    ui->setupUi(this);

    m_pListW = new QListWidget(this);
    m_pListW->addItem("好友");
    m_pListW->addItem("图书");
}

OpeWidget::~OpeWidget() {
    delete ui;
}
