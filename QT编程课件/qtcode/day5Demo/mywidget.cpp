#include "mywidget.h"
#include "ui_mywidget.h"
#include <QKeyEvent>
#include <QDebug>
#include "controlform.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //引入组件类
    ControlForm* cf = new ControlForm(this);


    //关联自定义的信号和槽
    connect(this,&MyWidget::sendMsg,cf,&ControlForm::recvMsg);
    connect(this,&MyWidget::sendMsg,ui->widget,&ControlForm::recvMsg);

    //关联按钮点击时发送信号
    connect(ui->volButton,&QPushButton::clicked,this,[=](){
        //发起信号
        emit sendMsg(0,"静音",3.14);//
        ui->volButton->setEnabled(false);
    });

    connect(ui->ligButton,&QPushButton::clicked,this,[=](){
        //发起信号
        emit sendMsg(100,"刺眼",0.618);//
        ui->ligButton->setEnabled(false);
    });
}

MyWidget::~MyWidget()
{
    delete ui;
}


//覆写事件函数
void MyWidget::keyPressEvent(QKeyEvent *event){
    //事件函数的第一个参数就是事件对象【封装了事件的细节】
    qDebug() << event->key();
    ui->label->setText("key:"+event->key());
}
