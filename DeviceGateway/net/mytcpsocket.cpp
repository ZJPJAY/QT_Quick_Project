#include "mytcpsocket.h"
#include <QDebug>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include "myserialport.h"

MyTcpSocket * MyTcpSocket::mtsObj = nullptr;

MyTcpSocket::MyTcpSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this,
            &MyTcpSocket::readyRead,
            this,
            &MyTcpSocket::readyReadSlot);

    qDebug() << "[+] New Tcp Conecting!";
}

MyTcpSocket *MyTcpSocket::getObject()
{
    if(mtsObj == nullptr)
        mtsObj = new MyTcpSocket;
    return mtsObj;
}

void MyTcpSocket::sendDataTem(double value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":1001,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendDataHum(double value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":1002,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendDataLig(double value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":1003,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendDataUlt(int value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":1004,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendDataCo2(int value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":1005,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendDataPm(int value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":1006,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendSignalLig(int value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":2001,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::sendSignalAle(int value)
{
    MyTcpSocket::getObject()->write("{\"Sender\":\"gateway\",\"Name\":2002,\"Value\":" +
                                    QString::number(value).toLatin1() + "}");
}

void MyTcpSocket::readyReadSlot()
{
    QByteArray data;
    data = this->readAll();//?????????????????????data?????????
    qDebug() << QString("").fill('>',25).toUtf8().data();

    QHostAddress tmp;
    tmp.setAddress(this->peerAddress().toIPv4Address());
    qDebug() << tmp.toString().toUtf8().data() << ":" << this->peerPort() <<QString(data).toUtf8().data();
    handleData(data);//??????data?????????????????????????????????????????????
    qDebug() << QString("").fill('<',25).toUtf8().data();
}

void MyTcpSocket::handleData(QByteArray data)//???????????????Json????????????
{
    temp.append(data);
    int count = 0;

    for(int i =0;i < temp.length();i++){
        if(temp.at(i) == '{'){
            if(count == 0){
                temp = temp.mid(i,temp.length());//???????????????{??????{???????????????????????????
                i = 0;
                count++;
                continue;
            }
            count++;
        }
        if(temp.at(i) == '}'){
            count--;
            if(count == 0){
                QByteArray frame = temp.mid(0,i+1);//???????????????????????????????????????
                handleFrame(frame);//??????????????????
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

    if(obj.contains("Sender")){//??????????????????????????????
        if(obj.value("Sender") == "access layer"){
            obj.remove("Sender");
            qDebug() << obj;
        }
        else if(obj.value("Sender") == "back end"){

            if(obj.value("Name").toInt() == 2001){//?????????????????????,?????????
                if(obj.value("Value") == 1)qDebug() << "AlarmLight On";
                if(obj.value("Value") == 0)qDebug() << "AlarmLight Off";
                MySerialPort::getObject()->controlLight((unsigned char)obj.value("Value").toInt());
            }
            else if(obj.value("Name").toInt() == 2002){//?????????????????????,?????????
                if(obj.value("Value") == 1)qDebug() << "AlarmLight On";
                if(obj.value("Value") == 0)qDebug() << "AlarmLight Off";
                MySerialPort::getObject()->controlAlert((unsigned char)obj.value("Value").toInt());
            }
            else if(obj.value("Name").toInt() == 1001){
                sendDataTem(obj.value("Value").toDouble());
                qDebug() << "Sending Temperature Data";
            }
            else if(obj.value("Name").toInt() == 1002){
                sendDataHum(obj.value("Value").toDouble());
                qDebug() << "Sending Humidity Data";
            }
            else if(obj.value("Name").toInt() == 1003){
                sendDataLig(obj.value("Value").toDouble());
                qDebug() << "Sending LightIntensity Data";
            }
            else if(obj.value("Name").toInt() == 1004){
                sendDataUlt(obj.value("Value").toInt());
                qDebug() << "Sending UltraRays Data";
            }
            else if(obj.value("Name").toInt() == 1005){
                sendDataCo2(obj.value("Value").toInt());
                qDebug() << "Sending CO2 Data";
            }
            else if(obj.value("Name").toInt() == 1006){
                sendDataPm(obj.value("Value").toInt());
                qDebug() << "Sending PM2.5 Data";
            }
        }
    }
}
