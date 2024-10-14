#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>


#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void onReplied(QNetworkReply *reply);

    void GetNetJson();
    void GetNetImgJson(QString url);

    void fromNetJson(QByteArray &byteArr);

    void onRepliedImg(QNetworkReply *replyImg);
    void fromJsonImg(QByteArray &JsonImg);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //http
    QNetworkAccessManager * NetAccessManager;
    QNetworkAccessManager * ImgNetAccessManager;

    QString ImgUrl =  QString("http://v.api.aa1.cn/api/api-gqsh/img/259.jpg");

    QPixmap *currentPicture;

    QByteArray ByteImg;

};
#endif // MAINWINDOW_H

