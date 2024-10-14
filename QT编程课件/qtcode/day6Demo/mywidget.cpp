#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFile>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //关联信号和槽
    connect(ui->commandLinkButton,&QPushButton::clicked,this,[=](){
        //逻辑
        emit mySignal("您已同意",0);
    });

    //遇到函数重载 需要使用函数指针
    void (AccessForm::* afqi)(QString,int)  = &AccessForm::mySlot;
    void (AccessForm::* afq)(QString)  = &AccessForm::mySlot;
    connect(this,&MyWidget::mySignal,ui->widget,afq);


    //关联设置样式的槽函数
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        //使用样式
        QString str;
        QFile file(":/style/resource/dark.qss");
        if(file.open(QIODevice::ReadOnly)){
            str = file.readAll();
            file.close();
        }
        qDebug() << str;
        this->setStyleSheet(str);
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        //使用样式
        QString str;
        QFile file(":/style/resource/regular.qss");
        if(file.open(QIODevice::ReadOnly)){
            str = file.readAll();
            file.close();
        }
        qDebug() << str;
        this->setStyleSheet(str);
    });
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    //使用样式
    // QString str;
    // QFile file(":/style/resource/dark.qss");
    // if(file.open(QIODevice::ReadOnly)){
    //     str = file.readAll();
    //     file.close();
    // }
    // qDebug() << str;
    // this->setStyleSheet(str);
}

