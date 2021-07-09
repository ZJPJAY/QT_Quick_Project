#include "mywindow.h"
#include "ui_mywindow.h"
#include <QMouseEvent>

MyWindow::MyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,
            &QPushButton::clicked,
            this,
            &MyWindow::slotsTest1);
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_pushButton_clicked(){
    this->setWindowTitle("Fuck");
}

void MyWindow::slotsTest1(){

}

void MyWindow::slotsTest2(){
    this->setWindowTitle("Hello");
}

void MyWindow::mousePressEvent(QMouseEvent *e){
    isPress = true;
    oldPos = e->pos();
}
void MyWindow::mouseReleaseEvent(QMouseEvent *){
}
void MyWindow::mouseMoveEvent(QMouseEvent *e){
    if(!isPress)
        return;
   this->move(e->pos() - oldPos + this->pos());
}
