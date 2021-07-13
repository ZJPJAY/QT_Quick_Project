#include "mytcpsocket.h"
#include <QDebug>
#include "sqlexec.h"
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>

MyTcpSocket::MyTcpSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this,
            &MyTcpSocket::readyRead,
            this,
            &MyTcpSocket::readyReadSlot);

    connect(this,
            &MyTcpSocket::disconnected,
            this,
            &MyTcpSocket::disconnectedSlot);
}

void MyTcpSocket::setDB(SqlExec *db)
{
    sqlExec = db;
}

void MyTcpSocket::readyReadSlot()
{
    QByteArray data;
    data = this->readAll();
    qDebug() << data;
    handleData(data);
}

void MyTcpSocket::disconnectedSlot()
{
    emit socketDisconnected(thread());
}

void MyTcpSocket::handleData(QByteArray data)
{
    temp.append(data);
    int count = 0;

    for(int i =0;i < temp.length();i++){
        if(temp.at(i) == '{'){
            if(count == 0){
                temp = temp.mid(i,temp.length());//找到第一个{，把{前面的字符全部删掉
                i = 0;
                count++;
                continue;
            }
            count++;
        }
        if(temp.at(i) == '}'){
            count--;
            if(count == 0){
                QByteArray frame = temp.mid(0,i+1);//得到了完整的有头有尾的数据
                handleFrame(frame);//解析数据内容
                temp = temp.mid(i+1,temp.length());
                i = -1;
                continue;
            }
        }
    }
}

void MyTcpSocket::handleFrame(QByteArray data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    if(obj.value("AlarmLight").toInt() == 2001){//得到键值进行比对
        qDebug() << "AlarmLight On/Off";
    }
    if(obj.value("AlarmAlert").toInt() == 2002){
        qDebug() << "AlarmAlert On/Off";
    }

}
