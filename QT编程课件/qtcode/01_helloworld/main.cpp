#include "mywidget.h"
// 包含第一个图形界面的  声明文件  .h
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//创建 Qt应用程序对象
    MyWidget w;//创建第一个图形界面对象，使用空参构造函数创建，在内存的栈
    w.show();//调用 继承 QWidget 的show方法显示图形窗口
    // MyWidget* w1 = new MyWidget();//使用空参构造在  堆创建对象， 栈中使用 w1作为引用
    // w1->show();
    return a.exec();//应用程序对象开启循环事件监听的  阻塞
}
