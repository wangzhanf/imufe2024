#include "accessform.h"
#include "ui_accessform.h"

AccessForm::AccessForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccessForm)
{
    ui->setupUi(this);
    //给按钮添加图标
    ui->pushButton->setIcon(QIcon(":/img/resource/video.png"));
}

AccessForm::~AccessForm()
{
    delete ui;
}


void AccessForm::mySlot(QString str,int num){
    ui->pushButton->setText(QString("%1(%2)").arg(str).arg(num));
}
void AccessForm::mySlot(QString str){
    ui->pushButton->setText(QString("%1(9)").arg(str));
}
