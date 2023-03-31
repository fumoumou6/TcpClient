//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_BOOK_H
#define TCPCLIENT_BOOK_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class book; }
QT_END_NAMESPACE

class book : public QWidget {
Q_OBJECT

public:
    explicit book(QWidget *parent = nullptr);

    ~book() override;

private:
    Ui::book *ui;
};


#endif //TCPCLIENT_BOOK_H
