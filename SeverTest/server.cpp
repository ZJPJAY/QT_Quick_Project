#include "server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer)
{
    server->listen(QHostAddress::Any,10001);

    connect(server,
            &QTcpServer::newConnection,
            this,
            &Server::newConnectionSlot);

}

void Server::sendDataToAllClient(const QByteArray &data)
{
    foreach(QTcpSocket *socket,socketList){
        socket->write(data);
    }

}

void Server::newConnectionSlot()
{

    qDebug() << "[+] New Connection!";
    QTcpSocket *socket = server->nextPendingConnection();

    socketList.append(socket);

    socket->write("Hello");
    connect(socket,
            &QTcpSocket::readyRead,
            this,
            &Server::socketReadyReadSlot);

    connect(socket,
            &QTcpSocket::disconnected,
            this,
            &Server::socketDisconnectedSlot);

    connect(socket,
            &QTcpSocket::stateChanged,
            this,
            &Server::stateChange);

}

void Server::socketReadyReadSlot()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *> (sender());

    QByteArray data;
    data = socket->readAll();
    //QString str = QString::fromLocal8Bit(data);
    //qDebug() << str;

    sendDataToAllClient("[" +
                        socket->peerAddress().toString().toLocal8Bit() +
                        "]" + data);
}

void Server::socketDisconnectedSlot()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *> (sender());

    socketList.removeOne(socket);
    qDebug() << "[-] Remove one Connection!";
}

void Server::stateChange()
{
    qDebug() << "State Changed!";
}
