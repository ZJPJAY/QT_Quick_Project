#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
protected:
    explicit MyTcpSocket(QObject *parent = nullptr);

public:
    static MyTcpSocket *getObject();

    void sendDataTem(double value);
    void sendDataHum(double value);
    void sendDataLig(double value);
    void sendDataUlt(int value);
    void sendDataCo2(int value);
    void sendDataPm(int value);

    void sendSignalLig(int value);
    void sendSignalAle(int value);

protected slots:
    void readyReadSlot();

protected:
    void handleData(QByteArray data);//解析tcp数据,得到完整的一组数据
    void handleFrame(QByteArray data);//解析Json数据,将完整的数据输入
    QByteArray temp;//缓存数据

    static MyTcpSocket *mtsObj;

};

#endif // MYTCPSOCKET_H
