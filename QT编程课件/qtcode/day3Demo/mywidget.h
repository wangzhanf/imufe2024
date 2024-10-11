#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

//前向声明
class MyMainWindow;

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
    virtual void mousePressEvent(QMouseEvent *);//声明事件函数覆写
    virtual void resizeEvent(QResizeEvent *);
    virtual void keyPressEvent(QKeyEvent *);

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MyWidget *ui;
    MyMainWindow* mmw = nullptr;
};
#endif // MYWIDGET_H
