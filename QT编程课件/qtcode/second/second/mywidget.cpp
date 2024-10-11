#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDialog>
#include <QFileDialog>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //加载广告窗口
    QDialog* broad = new QDialog();
    //getter和setter
    broad->setWindowTitle("welcome 5 seconds");
    broad->setGeometry(200,200,400,400);
    // broad->setModal(true);
    // broad->show();
    broad->exec();

    //绝对定位
    // 获取当前窗口的宽度
    int winWidth = this->geometry().width();
    ui->pushButton->setGeometry(winWidth*0.1,100,winWidth*0.8,100);

    //让密码输入框只读
    // ui->lineEdit_2->setReadOnly(true);
    //tab顺序
    // this->setTabOrder(ui->lineEdit);

    //构造主应用程序窗口
    this->mmw = new MyMainWindow();
}

MyWidget::~MyWidget()
{
    delete ui;
    delete mmw;
}
//槽函数，  事件发生时的既定处理措施
void MyWidget::on_pushButton_clicked()
{
    // QString fname = QFileDialog::getOpenFileName(this,"打开压缩文件","C:/IAR","压缩文件(*zip *rar)");
    // qDebug() << fname;
    //打开主界面窗口
    this->mmw->show();
    this->hide();
}

