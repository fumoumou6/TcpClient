#include "UI/login/tcpclient.h"

#include <QApplication>

#include "UI/ope/OpeWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpClient w;
    w.show();

//OpeWidget W;
//W.show();
    return a.exec();
}
