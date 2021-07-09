#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>

class Client;

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();

private slots:
    void readDataSlot(QByteArray data);

    void on_leSendData_returnPressed();

private:
    Ui::ChatPage *ui;
    Client *client;
};

#endif // CHATPAGE_H
