//定义文件
#include "mywidget.h"
#include "ui_mywidget.h"
#include <QLabel>
#include <QDialog>
#include <QColorDialog>
#include <QDebug>

//构造函数的定义   类名 域解析符 属性名或函数名 (形参列表[默认值只能在声明或定义时出现1次])
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)    //  :初始化列表（调用基类的构造函数）
    , ui(new Ui::MyWidget) // 通过  匿名对象构造
{
    ui->setupUi(this);//初始化界面，放在第一行
    // new int[1024*1024*4];
    // 所有图形界面下的组件都被封装到  ui中  ,  uic编译器实现
    // ui->pushButton->setText("点击登录");
    ui->commandLinkButton->setDisabled(true);
    ui->commandLinkButton->hide();

    //创建一个label用以显式文字
    QLabel* lab1 = new QLabel("我的名字",this);//默认是顶级窗口，指定父对象后称为子部件
    // lab1->show();
    // 创建一个 对话框   QDialog【顶级窗口】 ，里面显示   QLabel【子部件】
    // QDialog d1;//栈
    // d1.show();//函数运行结束，栈销毁   ，会出现闪退
    // d1.exec();//产生一个  顶级窗口    ，  阻塞程序运行  ，  可以获取其返回值   ，  形成了模态框
    QDialog* d2 = new QDialog();//创建一个堆内对象，不指定父窗口则为顶级窗口
    d2->geometry();//获取其几何布局，此处代码仅用以演示getter的用法
    d2->setWindowTitle("welcome");//此处代码演示setter的用法
    d2->setGeometry(200,400,800,600);
    d2->setFixedSize(400,400);//设定窗口大小为固定，不能更改其尺寸
    QLabel* lab2 = new QLabel("haha",d2);//创建一个堆内对象，直接指定其父窗口，销毁时由其父窗口负责销毁内存空间
    lab2->setGeometry(QRect(200,200,300,100));
    d2->show();//显式调用show()方法展示窗口

}
//析构函数
MyWidget::~MyWidget()
{
    delete ui;
}
//槽函数的定义
void MyWidget::on_pushButton_clicked()
{
    // this->close();
    QColorDialog qcd(Qt::blue,this);
    qcd.exec();
    QColor col = qcd.currentColor();
    //调试输出方法
    qDebug() << col;

    //点击按钮打开文件对话框，选择   zip和rar文件， 在控制台输出文件名称
}

