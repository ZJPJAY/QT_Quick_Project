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
    QTcpSocket *socket = qobject_cast <QTcpSocket *> (sender());

    QByteArray datarec = socket->readAll();//读取客户端发送来的所有数据，包括目标IP地址和端口
    QByteArray datauser = QString(datarec).mid(25).toLocal8Bit();//得到客户端的文本数据，不包含IP地址和端口

    QString dataaddr1 = QString(datarec).mid(0,23);
    //dataaddr1确认用户是否发送地址和端口数据并获取,内容为IP地址和端口

    if(dataaddr1.indexOf(":")==-1){

        sendDataToAllClient("[+] without address and port data");

        QHostAddress temphost;         //定义temphost变量来存已经转换好的客户端ipv4地址
        temphost.setAddress(socket->peerAddress().toIPv4Address());

        sendDataToAllClient("[" +
                            temphost.toString().toLocal8Bit() +
                            ":" + QString::number(socket->peerPort()).toLocal8Bit() +
                            "]" + datauser);
    }
    else {
        int portpos = dataaddr1.indexOf(":") + 1;

        QString dataport = QString::number(dataaddr1.mid(portpos,portpos+3).toInt());
        //得到Qstring类型的客户端上传的接收端的端口
        QHostAddress dataaddr(dataaddr1.mid(0,portpos-1));
        //得到QHostAddress类型的客户端上传的接收端的IPv4地址

        QHostAddress temphost;         //定义temphost变量来转换客户端发送端IPv6地址
        temphost.setAddress(socket->peerAddress().toIPv4Address());

        foreach(QTcpSocket *socket1, socketList){
            QHostAddress paddr;
            paddr.setAddress(socket1->peerAddress().toIPv4Address());
            //paddr为列表转换后的指向客户端的IPv4地址

            if(paddr.toString().toLocal8Bit() == dataaddr1.mid(0,portpos-1).toLocal8Bit()){
                //判断socketList列表内是否存在相应的IP地址
                if(socket1->peerPort() == dataport.toUShort()){
                    //判断socketList列表内是否存在相应的端口

                    socket1->write("[+] [" + temphost.toString().toLocal8Bit() +
                                   ":" + QString::number(socket->peerPort()).toLocal8Bit() + "]" +
                                   " to " + "[" + paddr.toString().toLocal8Bit() +
                                   ":" + QString::number(dataport.toUShort()).toLocal8Bit() + "]" +
                                   datauser);

                    if(socket1->peerPort() != socket->peerPort()){
                        socket->write("[+] [" + temphost.toString().toLocal8Bit() +
                                      ":" + QString::number(socket->peerPort()).toLocal8Bit() + "]" +
                                      " to " + "[" + paddr.toString().toLocal8Bit() +
                                      ":" + QString::number(dataport.toUShort()).toLocal8Bit() + "]" +
                                      datauser);
                    }
                }
            }
        }



        /*失败作品，无法重新连接新地址和端口
        int portpos = dataaddr1.indexOf(":") + 1;
        QString dataport1 = dataaddr1.mid(portpos,portpos+3);
        QString dataport2 = QString::number(dataport1.toInt());
        QByteArray dataaddr = dataaddr1.toLocal8Bit();

        QHostAddress senderaddr = socket->peerAddress();
        unsigned short senderport = socket->peerPort();

        socket->connectToHost(dataaddr,dataport2.toUShort());
        QHostAddress temphost;         //定义temphost变量来存已经转换好的客户端ipv4地址
        temphost.setAddress(socket->peerAddress().toIPv4Address());

        socket->write("[" +
                      temphost.toString().toLocal8Bit() +
                      ":" + QString::number(socket->peerPort()).toLocal8Bit() +
                      "]" + datauser + dataport2.toLocal8Bit());
        socket->write("[+] success");

        socket->connectToHost(senderaddr,senderport);
        */
    }


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
