//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_book.h" resolved

#include "book.h"
#include "ui_book.h"


book::book(QWidget *parent) :
        QWidget(parent), ui(new Ui::book) {
    ui->setupUi(this);
}

book::~book() {
    delete ui;
}
