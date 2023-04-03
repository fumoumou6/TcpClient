#include "UI/login/tcpclient.h"
#include "UI/ope/OpeWidget.h"
#include <QApplication>

//#include "UI/ope/OpeWidget.h"
//#include "UI/online/online.h"
//#include "UI/friend/friend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    TcpClient w;
//    w.show();

//online W;
//W.show();
//Friend W;
//W.show();
OpeWidget w;
w.show();
    return a.exec();
}
