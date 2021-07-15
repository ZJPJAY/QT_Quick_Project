#include "mainpage.h"
#include "ui_mainpage.h"
#include "mytcpsocket.h"
#include "myserialport.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

    ui->cbSerialPortList->addItems(MySerialPort::getObject()->getPortList());

    connect(MyTcpSocket::getObject(),
            &MyTcpSocket::connected,
            this,
            &MainPage::netConnectedSlot);

    connect(MyTcpSocket::getObject(),
            &MyTcpSocket::disconnected,
            this,
            &MainPage::netDisconnectedSlot);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_btnNetConnect_clicked()
{
    MyTcpSocket::getObject()->connectToHost(ui->leNetIP->text(),ui->leNetPort->text().toUShort());
}

void MainPage::netConnectedSlot()
{
    ui->btnNetConnect->setEnabled(false);
}

void MainPage::netDisconnectedSlot()
{
    ui->btnNetConnect->setEnabled(true);
}

void MainPage::on_btnSerialOpen_clicked()
{
    MySerialPort::getObject()->setPortName(ui->cbSerialPortList->currentText());

    bool ok = MySerialPort::getObject()->open(QIODevice::ReadWrite);
    if(ok)
        ui->btnSerialOpen->setEnabled(false);
}

void MainPage::on_btnTest_clicked()
{
    MySerialPort::getObject()->controlLight(1);
}
