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

    connect(socket,
            &MyTcpSocket::sendData,
            this,
            &MyTcpServer::sendData);
    //该connect绑定了MyTcpSocket的sendData信号到MyTcpServer的同名信号上

    connect(this,
            &MyTcpServer::sendData,
            socket,
            &MyTcpSocket::sendDataSlot);
    //该connect绑定了MyTcpServer上的sendData信号到MyTcpSocket的sendDataSlot槽函数上
    //即任意一个socket触发了sendData信号都会激发每个绑定了以上两个信号的所有socket的sendData

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


