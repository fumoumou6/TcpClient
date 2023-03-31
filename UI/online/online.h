//
// Created by fumoumou on 23-3-31.
//

#ifndef TCPCLIENT_ONLINE_H
#define TCPCLIENT_ONLINE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class online; }
QT_END_NAMESPACE

class online : public QWidget {
Q_OBJECT

public:
    explicit online(QWidget *parent = nullptr);

    ~online() override;

private:
    Ui::online *ui;
};


#endif //TCPCLIENT_ONLINE_H
