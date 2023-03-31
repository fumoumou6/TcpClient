//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_online.h" resolved

#include "online.h"
#include "ui_online.h"


online::online(QWidget *parent) :
        QWidget(parent), ui(new Ui::online) {
    ui->setupUi(this);
}

online::~online() {
    delete ui;
}
