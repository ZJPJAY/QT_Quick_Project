#include "mytcpserver.h"
#include "mytcpsocket.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{

}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    MyTcpSocket *socket = new MyTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,
            &MyTcpSocket::disconnected,
            this,
            &MyTcpServer::socketDisconnectedSlot);
}

void MyTcpServer::socketDisconnectedSlot()
{
    MyTcpSocket *socket = qobject_cast<MyTcpSocket *> (sender());
    socket->deleteLater();
}


