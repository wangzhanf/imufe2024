//定义文件
#include "mywidget.h"
#include "ui_mywidget.h"

//构造函数的定义   类名 域解析符 属性名或函数名 (形参列表[默认值只能在声明或定义时出现1次])
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)    //  :初始化列表（调用基类的构造函数）
    , ui(new Ui::MyWidget) // 通过  匿名对象构造
{
    ui->setupUi(this);//初始化界面，放在第一行
    // new int[1024*1024*4];
    // 所有图形界面下的组件都被封装到  ui中  ,  uic编译器实现
    ui->pushButton->setText("点击登录");
}
//析构函数
MyWidget::~MyWidget()
{
    delete ui;
}
