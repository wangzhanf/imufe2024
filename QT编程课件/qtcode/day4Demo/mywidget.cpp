#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPushButton>
#include <QLabel>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //创建两个组件   button   和  label  ，点击button 后   label产生改变
    QPushButton* btn1 = new QPushButton("btn",this);
    btn1->setGeometry(10,10,100,50);
    QLabel* lab1 = new QLabel("lab",this);
    lab1->setGeometry(10,150,100,50);
    //connect(信号发起者，发起的信号，信号接收者，调用的槽函数);
    //Qt4 信号和槽看懂即可，不推荐，因为没有类型检查
    //SIGNAL和SLOT是两个宏，仅仅做字符串匹配，只有在运行时才会发现问题
    connect(btn1,SIGNAL(clicked),lab1,SLOT(setText));


    //信号和槽之间需要传递信息
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)));
    // connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,[=](){
    //         //函数式编程   lambda
    // });
}

MyWidget::~MyWidget()
{
    delete ui;
}
