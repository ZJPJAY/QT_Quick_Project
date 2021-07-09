#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>

namespace Ui {
class MyWindow;
}

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

private slots:
    void on_pushButton_clicked();
    void slotsTest1();
    void slotsTest2();


private:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    Ui::MyWindow *ui;

    QPoint oldPos;
    bool isPress;
};

#endif // MYWINDOW_H
