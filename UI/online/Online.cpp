//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Online.h" resolved

#include "Online.h"
#include "ui_Online.h"


Online::Online(QWidget *parent) :
        QWidget(parent), ui(new Ui::Online) {
    ui->setupUi(this);
}

Online::~Online() {
    delete ui;
}
