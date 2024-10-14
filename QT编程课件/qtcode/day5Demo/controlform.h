#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(QWidget *parent = nullptr);
    ~ControlForm();

//声明槽函数
public slots:
    void recvMsg(int,QString);//对应信号，可以少于信号的形参

private:
    Ui::ControlForm *ui;
};

#endif // CONTROLFORM_H
