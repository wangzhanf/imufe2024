#include "controlform.h"
#include "ui_controlform.h"

ControlForm::ControlForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlForm)
{
    ui->setupUi(this);
    //通过信号和槽实现关联
    //Qt4 不推荐   ，  运行时检查
    //connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)));
    //Qt5推荐   ,编译时检查
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
    //connect(ui->spinBox,&QSpinBox::valueChanged,ui->horizontalSlider,&QSlider::setValue);
    //C++典型的【面向结构，面向对象，函数式编程，模板元编程】，面向对象有一个特点【覆写/重载】 ，QSpinBox  setValue（int|string）
    //因为重载形成歧义， 可以通过 函数指针  消除歧义
    //1 定义函数指针
    void (QSpinBox::* qsbi)(int) = &QSpinBox::valueChanged;//函数后面带括号，代表运行该函数 ， 函数名称就是函数的地址，函数指针
    void (QSlider:: * qsi)(int) = &QSlider::setValue;
    connect(ui->spinBox,qsbi,ui->horizontalSlider,qsi);//规避函数调用的二义性

    //当触发信号的时候，需要执行复杂业务，可以通过 函数式编程（匿名函数  -- lambda表达式）
    connect(ui->spinBox,qsbi,this,[=](){
        int temp = this->ui->spinBox->value();
        if(temp > 30 && temp < 60)
            this->ui->label->setText(QString("%1%2").arg(temp).arg("%"));
    });
}



ControlForm::~ControlForm()
{
    delete ui;
}


//定义槽函数
void ControlForm::recvMsg(int val,QString str){
    ui->horizontalSlider->setValue(val);
    ui->label->setText(str);
}
