#include "chatpage.h"
#include "ui_chatpage.h"
#include "client.h"

ChatPage::ChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatPage)
    , client(new Client)
{
    ui->setupUi(this);

    connect(client,
            &Client::readData,
            this,
            &ChatPage::readDataSlot);

}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::readDataSlot(QByteArray data)
{
    QString str;
    str = QString::fromLocal8Bit(data);
    ui->tbReadData->append(str);

}

void ChatPage::on_leSendData_returnPressed()
{
    if(ui->leSendAddress->text().toLocal8Bit().length() == 0){
        QString str ;
        str.fill(' ',25);

        client->sendData(str.toLocal8Bit() + ui->leSendData->text().toLocal8Bit());
    }
    else {
        QString str;
        str.fill(' ',25-ui->leSendAddress->text().length());

        client->sendData(ui->leSendAddress->text().toLocal8Bit() + str.toLocal8Bit() + ui->leSendData->text().toLocal8Bit());
    }

}
