#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket * myTcpClient;//当前客户端
    QTcpServer * myTcpServer;//对应的服务器
    bool connectStatus;//当前客户端的连接状态
    void init();//初始化函数

private slots:
    void on_connectServerBtn_clicked();
    void on_SendBtn_clicked();

    void slotConnected();
    void slotReadyRead();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError error);
};
#endif // WIDGET_H
