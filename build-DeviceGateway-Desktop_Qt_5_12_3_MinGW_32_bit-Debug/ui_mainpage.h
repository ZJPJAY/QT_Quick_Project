/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QGroupBox *groupBox;
    QComboBox *cbSerialPortList;
    QPushButton *btnSerialOpen;
    QGroupBox *groupBox_2;
    QLineEdit *leNetPort;
    QLineEdit *leNetIP;
    QPushButton *btnNetConnect;
    QPushButton *btnTest;

    void setupUi(QWidget *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName(QString::fromUtf8("MainPage"));
        MainPage->resize(696, 445);
        groupBox = new QGroupBox(MainPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(70, 80, 221, 171));
        cbSerialPortList = new QComboBox(groupBox);
        cbSerialPortList->setObjectName(QString::fromUtf8("cbSerialPortList"));
        cbSerialPortList->setGeometry(QRect(10, 20, 69, 22));
        btnSerialOpen = new QPushButton(groupBox);
        btnSerialOpen->setObjectName(QString::fromUtf8("btnSerialOpen"));
        btnSerialOpen->setGeometry(QRect(130, 20, 75, 23));
        groupBox_2 = new QGroupBox(MainPage);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 80, 261, 171));
        leNetPort = new QLineEdit(groupBox_2);
        leNetPort->setObjectName(QString::fromUtf8("leNetPort"));
        leNetPort->setGeometry(QRect(20, 50, 113, 20));
        leNetIP = new QLineEdit(groupBox_2);
        leNetIP->setObjectName(QString::fromUtf8("leNetIP"));
        leNetIP->setGeometry(QRect(20, 20, 113, 20));
        btnNetConnect = new QPushButton(groupBox_2);
        btnNetConnect->setObjectName(QString::fromUtf8("btnNetConnect"));
        btnNetConnect->setGeometry(QRect(150, 50, 75, 23));
        btnTest = new QPushButton(MainPage);
        btnTest->setObjectName(QString::fromUtf8("btnTest"));
        btnTest->setGeometry(QRect(280, 270, 75, 23));

        retranslateUi(MainPage);

        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QWidget *MainPage)
    {
        MainPage->setWindowTitle(QApplication::translate("MainPage", "MainPage", nullptr));
        groupBox->setTitle(QApplication::translate("MainPage", "SerialPort", nullptr));
        btnSerialOpen->setText(QApplication::translate("MainPage", "Open", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainPage", "Network", nullptr));
        leNetPort->setText(QApplication::translate("MainPage", "10001", nullptr));
        leNetPort->setPlaceholderText(QApplication::translate("MainPage", "Port", nullptr));
        leNetIP->setText(QApplication::translate("MainPage", "127.0.0.1", nullptr));
        leNetIP->setPlaceholderText(QApplication::translate("MainPage", "IP", nullptr));
        btnNetConnect->setText(QApplication::translate("MainPage", "Connect", nullptr));
        btnTest->setText(QApplication::translate("MainPage", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
