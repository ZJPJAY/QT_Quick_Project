#include "mytcpserver.h"
#include "mytcpsocket.h"
#include "mythread.h"
#include "threadhandle.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{

}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    MyTcpSocket *socket = new MyTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,
            &MyTcpSocket::socketDisconnected,
            this,
            &MyTcpServer::socketDisconnectedSlot);

    MyThread *thread = ThreadHandle::getObject()->getThread();
    socket->setDB(thread->getDB());
    socket->moveToThread(thread);
}

void MyTcpServer::socketDisconnectedSlot(QThread *th)
{
    MyTcpSocket *socket = qobject_cast<MyTcpSocket *> (sender());
    socket->deleteLater();
    ThreadHandle::getObject()->removeThread(qobject_cast<MyThread *>(th));
}


