#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //槽函数区域
private slots:
    void on_startServerBtn_clicked();//启动服务器按钮
    void slotNewConnection();//新的链接
    void slotReadyRead();
    void slotAcceptError(QAbstractSocket::SocketError error);
    void slotDisconnected();
    void on_clientSendBtn_clicked();
    void slotConnected();
private:
    Ui::Widget *ui;
    QTcpServer * myTcpServer = nullptr;//服务器端
    QTcpSocket *myTcpClient = nullptr;//新接入的客户端
    QList<QTcpSocket *> clients;//客户端列表   STL再封装  //数组，STL   【vector，list，map，set】

    void init();//初始化函数
};
#endif // WIDGET_H
