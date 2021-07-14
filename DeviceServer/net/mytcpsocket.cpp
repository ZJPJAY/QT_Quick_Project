#include "mytcpsocket.h"
#include <QDebug>
#include "sqlexec.h"
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>

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

    qDebug() << "[+] New Tcp Conecting!";
}

void MyTcpSocket::setDB(SqlExec *db)
{
    sqlExec = db;
}

void MyTcpSocket::sendDataSlot(QByteArray data)
{
    this->write(data);
}

void MyTcpSocket::readyReadSlot()
{
    QByteArray data;
    data = this->readAll();//读取所有数据到data中缓存
    qDebug() << QString("").fill('>',25).toUtf8().data();

    QHostAddress tmp;
    tmp.setAddress(this->peerAddress().toIPv4Address());
    qDebug() << tmp.toString().toUtf8().data() << ":" << this->peerPort(); //<<QString(data).toUtf8().data();
    handleData(data);//解析data中的数据并继续传输到相应的位置
    qDebug() << QString("").fill('<',25).toUtf8().data();
}

void MyTcpSocket::disconnectedSlot()
{
    emit socketDisconnected(thread());
}

void MyTcpSocket::handleData(QByteArray data)//解析完整的Json格式数据
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

    if(obj.contains("Sender")){//得到温度键值进行比对
        if(obj.value("Sender") == "gateway"){
            qDebug() << "Data:";
            qDebug() << "{";

            if(obj.value("Name") == 1001){
                qDebug() << "   Temperature: " << obj.value("Value").toDouble();

                this->sqlExec->addValue(this->sqlExec->selectValue("models_temperature")
                                        ,obj.value("Value").toDouble(),"models_temperature","temperature");
            }
            if(obj.value("Name") == 1002){
                qDebug() << "   Humidity: " << obj.value("Value").toDouble();

                this->sqlExec->addValue(this->sqlExec->selectValue("models_Humidity")
                                        ,obj.value("Value").toDouble(),"models_Humidity","humidity_consistence");
            }
            if(obj.value("Name") == 1003){
                qDebug() << "   LightIntensity: " << obj.value("Value").toDouble();

                this->sqlExec->addValue(this->sqlExec->selectValue("models_light")
                                        ,obj.value("Value").toDouble(),"models_light","illumination");
            }
            if(obj.value("Name") == 1004){
                qDebug() << "   UltraRays: " << obj.value("Value").toDouble();

                this->sqlExec->addValue(this->sqlExec->selectValue("models_uv")
                                        ,obj.value("Value").toInt(),"models_uv","ultraviolet_rays");
            }
            if(obj.value("Name") == 1005){
                qDebug() << "   CO2: " << obj.value("Value").toDouble();

                this->sqlExec->addValue(this->sqlExec->selectValue("models_co2")
                                        ,obj.value("Value").toInt(),"models_co2","co2_consistence");
            }
            if(obj.value("Name.5") == 1006){
                qDebug() << "   PM2.5: " << obj.value("Value").toDouble();

                this->sqlExec->addValue(this->sqlExec->selectValue("models_pm25")
                                        ,obj.value("Value").toInt(),"models_pm25","pm25_consistence");
            }
            qDebug() << "}";
            if(obj.value("Name") == 2001 || obj.value("Name") == 2002){
                //sendDataToAllClient(data);
                qDebug() << QString(data).toUtf8().data();
            }
        }
        else if(obj.value("Sender") == "access layer"){

        }
        else if(obj.value("Sender") == "back end"){
            if(obj.value("Name") == 2001 || obj.value("Name") == 2002){
                qDebug() << "   Signal: " << obj.value("Name").toInt() << "  Value: " << obj.value("Value").toInt();
                emit sendData(data);
                //触发MyTcpSocket的sendData信号，该信号在MyTcpServer中也定义了，所以可以在Server上两者相绑定
            }
        }
    }
}
