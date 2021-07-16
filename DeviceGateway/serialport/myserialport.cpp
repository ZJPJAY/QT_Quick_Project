#include "myserialport.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <mytcpsocket.h>
#include <QTimer>

MySerialPort * MySerialPort::mspObj = nullptr;

MySerialPort::MySerialPort(QObject *parent) : QSerialPort(parent)
{
    this->setBaudRate(57600);
    this->setDataBits(QSerialPort::Data8);
    this->setStopBits(QSerialPort::OneStop);
    this->setParity(QSerialPort::NoParity);
    this->setFlowControl(QSerialPort::NoFlowControl);

    connect(this,
            &MySerialPort::readyRead,
            this,
            &MySerialPort::readyReadSlot);

    sendTimer = new QTimer;
    appendTimer = new QTimer;
    //pushTimer = new QTimer;

    sendTimer->setInterval(1000);
    appendTimer->setInterval(10000);
    //pushTimer.setInterval(20000);

    connect(sendTimer,
            &QTimer::timeout,
            this,
            &MySerialPort::sendTimeoutSlot);
    connect(appendTimer,
            &QTimer::timeout,
            this,
            &MySerialPort::appendTimeoutSlot);
    /*connect(pushTimer,
            &QTimer::timeout,
            this,
            &MySerialPort::pushTimeoutSlot);*/

    sendTimer->start();
    appendTimer->start();
    //pushTimer->start();
}

MySerialPort *MySerialPort::getObject()
{
    if(mspObj == nullptr)
        mspObj = new MySerialPort;
    return mspObj;
}

QStringList MySerialPort::getPortList()
{
    QStringList list;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        list.append(info.portName());
    }
    return list;
}

void MySerialPort::requestTeAndHu()
{
    unsigned char buf[9];
    buf[0] = 0xFE;buf[1] = 0xFE;buf[2] = 0x00;buf[3] = 0xFF;buf[4] = 0xFF;

    buf[5] = 0x09;
    buf[6] = 0x02;
    buf[7] = 0x01;

    buf[8] = 0xFF;
    QByteArray data;
    data.append((char *)buf,9);
    //this->write(data);

    sendList.append(data);
}

void MySerialPort::requestLig()
{
    unsigned char buf[9];//FEFE00FFFF090203FF
    buf[0] = 0xFE;
    buf[1] = 0xFE;
    buf[2] = 0x00;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0x09;
    buf[6] = 0x02;
    buf[7] = 0x03;
    buf[8] = 0xFF;
    QByteArray data;
    data.append((char *)buf,9);
    sendList.append(data);
}

void MySerialPort::requestUlt()
{
    unsigned char buf[9];//FEFE00FFFF090204FF
    buf[0] = 0xFE;
    buf[1] = 0xFE;
    buf[2] = 0x00;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0x09;
    buf[6] = 0x02;
    buf[7] = 0x04;
    buf[8] = 0xFF;
    QByteArray data;
    data.append((char *)buf,9);
    sendList.append(data);
}

void MySerialPort::requestCo2()
{
    unsigned char buf[9];
    buf[0] = 0xFE;
    buf[1] = 0xFE;
    buf[2] = 0x00;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0x09;
    buf[6] = 0x02;
    buf[7] = 0x02;
    buf[8] = 0xFF;
    QByteArray data;
    data.append((char *)buf,9);
    sendList.append(data);
}

void MySerialPort::requestPm()
{
    unsigned char buf[9];//FEFE00FFFF090401FF
    buf[0] = 0xFE;
    buf[1] = 0xFE;
    buf[2] = 0x00;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0x09;
    buf[6] = 0x04;
    buf[7] = 0x01;
    buf[8] = 0xFF;
    QByteArray data;
    data.append((char *)buf,9);
    sendList.append(data);
}

void MySerialPort::controlLight(unsigned char con)
{
    unsigned char buf[10];
    buf[0] = 0xFE;buf[1] = 0xFE;buf[2] = 0x00;buf[3] = 0xFF;buf[4] = 0xFF;

    buf[5] = 0x09;
    buf[6] = 0x05;//5号节点板
    buf[7] = 0x01;//1号设备
    buf[8] = con;//请求开警报灯

    buf[9] = 0xFF;
    QByteArray data;
    data.append((char *)buf,10);
    //this->write(data);

    sendList.insert(0,data);
}

void MySerialPort::controlAlert(unsigned char con)
{
    unsigned char buf[10];
    buf[0] = 0xFE;buf[1] = 0xFE;buf[2] = 0x00;buf[3] = 0xFF;buf[4] = 0xFF;

    buf[5] = 0x09;
    buf[6] = 0x05;//5号节点板
    buf[7] = 0x02;//2号设备
    buf[8] = con;//请求开警报铃

    buf[9] = 0xFF;
    QByteArray data;
    data.append((char *)buf,10);
    //this->write(data);

    sendList.insert(0,data);
}

void MySerialPort::readyReadSlot()
{
    QByteArray data;
    data = this->readAll();//读取所有数据到data中缓存

    handleData(data);//解析data中的数据并继续传输到相应的位置
}

void MySerialPort::sendTimeoutSlot()
{
    if(!this->isOpen())
        return;
    if(sendList.isEmpty())
        return;

    QByteArray data = sendList.first();//得到发送列表第一个数据
    sendList.removeFirst();//发送该数据
    this->write(data);
}

void MySerialPort::appendTimeoutSlot()
{
    requestTeAndHu();
    requestLig();
    requestUlt();
    requestCo2();
    requestPm();

    //controlLight(unsigned char con);//开关警报灯
    //controlAlert(unsigned char con);//开关警报铃
}

void MySerialPort::handleData(QByteArray data)
{
    temp.append(data);//缓存这一帧数据

    if(temp.length() < 9)//帧长度最小为9
        return;

    for(int i = 1;i < temp.length();i++){
        if((unsigned char)temp.at(i) == 0xEF && (unsigned char)temp.at(i-1) == 0xEF){//查到帧头 0xEF 0xEF

            temp = temp.mid(i-1,temp.length());
            i = 0;
            if(temp.length() < 9)
                return;

            int len = temp.at(5);
            if(temp.length() < len)
                return;

            if((unsigned char)temp.at(len-1) != 0xFF){
                temp = temp.mid(2,temp.length());
                i = 0;
                continue;
            }
            QByteArray buff = temp.mid(0,len);//成功截取到一帧
            handleFrame(buff);

            temp = temp.mid(len,temp.length());//剩下的数据存起来
            i = 0;
            continue;
        }
    }
}

void MySerialPort::handleFrame(QByteArray data)
{
    unsigned char nodeID = (unsigned char)data.at(6);
    unsigned char devID = (unsigned char)data.at(7);
    unsigned char len = (unsigned char)data.at(5);

    if(nodeID == 0x02){
        if(devID == 0x01){//温湿度数据

            if(len-9 != 4)
                return;

            te = (unsigned char)data.at(8) + ((unsigned char)data.at(9) * 0.001);
            hu = (unsigned char)data.at(10) + ((unsigned char)data.at(11)  * 0.001);

            MyTcpSocket::getObject()->sendDataTem(te);
            MyTcpSocket::getObject()->sendDataHum(hu);
        }
        else if(devID == 0x02){

            if(len-9 != 2)
                return;

            co2 = (int)data.at(8)*255 + ((int)data.at(9));
            MyTcpSocket::getObject()->sendDataCo2(co2);
        }
        else if(devID == 0x03){

            if(len-9 != 2)
                return;

            lig = abs((double)data.at(8)) + (((double)data.at(9))*0.001);
            MyTcpSocket::getObject()->sendDataLig(lig);
        }
        else if(devID == 0x04){

            if(len-9 != 2)
                return;

            ur = (int)data.at(8)*255 + ((int)data.at(9));
            MyTcpSocket::getObject()->sendDataUlt(ur);
        }
        else
            qDebug() << "[-] Wrong DevID!";
    }
    else if(nodeID == 0x04){
        if(devID == 0x01){

            if(len-9 != 2)
                return;

            pm = (int)data.at(8)*255 + ((int)data.at(9));
            MyTcpSocket::getObject()->sendDataPm(pm);
        }
        else
            qDebug() << "[-] Wrong DevID!";
    }
    else
        qDebug() << "[-] Wrong NodeID!";

}
