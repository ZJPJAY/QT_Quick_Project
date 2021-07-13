#include <QCoreApplication>
#include "mytcpserver.h"
#include "threadhandle.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ThreadHandle::getObject();

    MyTcpServer s;
    s.listen(QHostAddress::Any, 10001);

    return a.exec();
}
