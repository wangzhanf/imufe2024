#ifndef MYWIDGET_H
#define MYWIDGET_H
// 头文件守卫  ，防止多次包含头文件

#include <QWidget>
//声明文件
//Qt 框架定义的宏， QT_BEGIN_NAMESPACE  防止变量污染
QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

// 定义一个类  MyWidget  ，该类  公共  继承了   QWidget基类
class MyWidget : public QWidget
{
    Q_OBJECT
    //Qt 框架定义的宏 , Qt的祖先类  ， 信号和槽，事件基于  Q_OBJECT，勿删，第一行

// 段 声明   ， 可以多次出现   , 允许Qt的特定段声明 【public slots】
public:
    MyWidget(QWidget *parent = nullptr);//构造函数， 使用了默认值 ， 找爹【自动内存回收】
    ~MyWidget();//析构函数，回收资源

private:
    Ui::MyWidget *ui;//在designer拖拽的组件  都会被封装到    ui

};
#endif // MYWIDGET_H
