#include "mywidget.h"
#include "ui_mywidget.h"
#include "mymainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QKeyEvent>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //获取当前窗口的宽度
    int w = this->geometry().width();
    //设置按钮的几何布局
    ui->pushButton->setGeometry(w*0.25,100,w*0.5,50);

    //初始化主应用程序窗口
    this->mmw = new MyMainWindow();



}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_3_clicked()
{
    //隐藏当前窗口
    this->hide();
    //显式主应用程序窗口
    this->mmw->show();
}


void MyWidget::mousePressEvent(QMouseEvent *eve){
    //定义自己的事件处理函数
    qDebug() << eve;
    qDebug() << eve->pos().x();
    qDebug() << eve->pos().y();
}

void MyWidget::resizeEvent(QResizeEvent *eve){
    //获取当前窗口的宽度
    int w = this->geometry().width();
    //设置按钮的几何布局
    ui->pushButton->setGeometry(w*0.25,100,w*0.5,50);
}

void MyWidget::keyPressEvent(QKeyEvent *e){
    qDebug() << e;
    qDebug() << e->key();
    int curX = ui->label->geometry().x();
    int curY = ui->label->geometry().y();
    int curW = ui->label->geometry().width();
    int curH = ui->label->geometry().height();
    if(e->key() == 87)
        ui->label->setGeometry(curX,curY-5,curW,curH);//ui->label->move()可以简化一些
    if(e->key() == 83)
        ui->label->move(curX,curY+5);
    if(e->key() == 63)
        ui->label->setGeometry(curX-5,curY,curW,curH);
    if(e->key() == 68)
        ui->label->setGeometry(curX+5,curY,curW,curH);
}

