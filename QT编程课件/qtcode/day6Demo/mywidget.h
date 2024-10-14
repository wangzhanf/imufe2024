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

signals:
    void mySignal(QString,int);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyWidget *ui;
};
#endif // MYWIDGET_H
