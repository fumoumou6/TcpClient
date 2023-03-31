//
// Created by fumoumou on 23-3-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_friend.h" resolved

#include "friend.h"
#include "ui_friend.h"


friend :: friend(QWidget
*parent) :

QWidget (parent), ui(new Ui:: friend) {
    ui->setupUi(this);
}

friend ::~
friend() {
delete
ui;
}
