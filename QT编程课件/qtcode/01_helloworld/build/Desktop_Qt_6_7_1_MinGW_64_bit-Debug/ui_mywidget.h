/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWidget
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QRadioButton *radioButton;
    QCommandLinkButton *commandLinkButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MyWidget)
    {
        if (MyWidget->objectName().isEmpty())
            MyWidget->setObjectName("MyWidget");
        MyWidget->resize(311, 229);
        pushButton = new QPushButton(MyWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 180, 80, 24));
        lineEdit = new QLineEdit(MyWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 170, 113, 23));
        label = new QLabel(MyWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 50, 121, 16));
        radioButton = new QRadioButton(MyWidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(130, 90, 97, 22));
        commandLinkButton = new QCommandLinkButton(MyWidget);
        commandLinkButton->setObjectName("commandLinkButton");
        commandLinkButton->setGeometry(QRect(130, 20, 168, 41));
        pushButton_2 = new QPushButton(MyWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(210, 140, 80, 24));

        retranslateUi(MyWidget);

        QMetaObject::connectSlotsByName(MyWidget);
    } // setupUi

    void retranslateUi(QWidget *MyWidget)
    {
        MyWidget->setWindowTitle(QCoreApplication::translate("MyWidget", "MyWidget", nullptr));
        pushButton->setText(QCoreApplication::translate("MyWidget", "\351\200\211\346\213\251\351\242\234\350\211\262", nullptr));
        label->setText(QCoreApplication::translate("MyWidget", "Hello World", nullptr));
        radioButton->setText(QCoreApplication::translate("MyWidget", "RadioButton", nullptr));
        commandLinkButton->setText(QCoreApplication::translate("MyWidget", "CommandLinkButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyWidget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWidget: public Ui_MyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
