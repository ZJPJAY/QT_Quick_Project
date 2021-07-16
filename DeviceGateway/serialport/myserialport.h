#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>
#include <QTimer>
#include <QStringList>

class MySerialPort : public QSerialPort
{
    Q_OBJECT
protected:
    explicit MySerialPort(QObject *parent = nullptr);

public:
    static MySerialPort *getObject();
    QStringList getPortList();

    void requestTeAndHu();
    void requestLig();
    void requestUlt();
    void requestCo2();
    void requestPm();

    void controlLight(unsigned char con);//开关警报灯
    void controlAlert(unsigned char con);//开关警报铃

protected slots:
    void readyReadSlot();
    void sendTimeoutSlot();
    void appendTimeoutSlot();
    //void pushTimeroutSlot();若数据都在一个表里面使用这个定时信号槽函数


protected:
    static MySerialPort *mspObj;
    void handleData(QByteArray data);//解析传输数据格式
    void handleFrame(QByteArray data);//解析数据内容

    QByteArray temp;//缓冲区

    QList<QByteArray> sendList;

    QTimer *sendTimer;
    QTimer *appendTimer;
    //QTimer *pushTimer;若数据都在一个表里面使用这个定时器，时间为上面appendTimer的时间间隔，一次性发送所有数据

    double te;
    double hu;
    double lig;
    int co2;
    int ur;
    int pm;

signals:

public slots:
};

#endif // MYSERIALPORT_H
