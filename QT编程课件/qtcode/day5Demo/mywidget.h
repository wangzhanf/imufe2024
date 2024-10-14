#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

//声明信号
signals:
    void sendMsg(int,QString,double);//int表示值， string表示传输的信息字段


private:
    Ui::MyWidget *ui;
    virtual void keyPressEvent(QKeyEvent *);
};
#endif // MYWIDGET_H
