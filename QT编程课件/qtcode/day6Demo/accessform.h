#ifndef ACCESSFORM_H
#define ACCESSFORM_H

#include <QWidget>

namespace Ui {
class AccessForm;
}

class AccessForm : public QWidget
{
    Q_OBJECT

public:
    explicit AccessForm(QWidget *parent = nullptr);
    ~AccessForm();

public slots:
    void mySlot(QString,int);   //  重载
    void mySlot(QString);    //overload

private:
    Ui::AccessForm *ui;
};

#endif // ACCESSFORM_H
