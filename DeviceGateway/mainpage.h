#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void on_btnNetConnect_clicked();
    void netConnectedSlot();
    void netDisconnectedSlot();

    void on_btnSerialOpen_clicked();

    void on_btnTest_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
