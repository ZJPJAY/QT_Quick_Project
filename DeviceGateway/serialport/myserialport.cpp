#include "myserialport.h"
#include <QSerialPortInfo>

MySerialPort * MySerialPort::mspObj = nullptr;

MySerialPort::MySerialPort(QObject *parent) : QSerialPort(parent)
{
    this->setBaudRate(57600);
    this->setDataBits(QSerialPort::Data8);
    this->setStopBits(QSerialPort::OneStop);
    this->setParity(QSerialPort::NoParity);
    this->setFlowControl(QSerialPort::NoFlowControl);

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
