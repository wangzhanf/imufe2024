#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NetAccessManager = new QNetworkAccessManager(this);
    ImgNetAccessManager = new QNetworkAccessManager(this);

    connect(NetAccessManager,&QNetworkAccessManager::finished,
            this,&MainWindow::onReplied);

    connect(ImgNetAccessManager,&QNetworkAccessManager::finished,
            this,&MainWindow::onRepliedImg);


    GetNetJson();
    GetNetImgJson(ImgUrl);
   // setWindowFlag(Qt::FramelessWindowHint); //设置无边框
    setFixedSize(width(),height());     //设置固定当前窗口大小
}

MainWindow::~MainWindow()
{
    delete ui;
}
//http 网络请求
void MainWindow::GetNetJson()
{
    QUrl url("https://v.api.aa1.cn/api/api-gqsh/index.php?wpon=json");
    NetAccessManager->get(QNetworkRequest(url));
}


void MainWindow::GetNetImgJson(QString url)
{
    ImgNetAccessManager->get(QNetworkRequest(url));
}

//获取json数据，其中包含图片url readall 存在byteArr中
//最后调用fromjson 解析出qstring imgurl
void MainWindow::onReplied(QNetworkReply *reply)
{

    qDebug()<<"网络请求成功";
    int satus_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"operation: "<<reply->operation();
    qDebug()<<"satus_code: "<<satus_code;
    qDebug()<<"url: "<<reply->url();
    qDebug()<<"raw header: "<<reply->rawHeaderList();
    if(reply->error() != QNetworkReply::NoError ||satus_code != 200 ){
        qDebug()<<reply->errorString().toLatin1().data();
        QMessageBox::warning(this,"QtNetImage","网络连接失败",QMessageBox::Ok);
    }else{
        QByteArray byteArray = reply->readAll();
        qDebug()<<"read all:" <<byteArray.data();

        //QPixmap Pixmap;
        //Pixmap.loadFromData(byteArray);
        fromNetJson(byteArray);
    }
    reply->deleteLater();
}

/*
{
    "error":0,
    "result":200,
    "img":"//v.api.aa1.cn/api/api-gqsh/img/305.jpg"
}
*/
//将imgurl 存储成员变量中
void MainWindow::fromNetJson(QByteArray &byteArr)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArr);
    if(!doc.isObject()){
        qDebug()<<"Netjson not an jsonObject!";
        return;
    }
    //2.开始解析
    QJsonObject obj = doc.object();
    ImgUrl = "http:" + obj.value("img").toString();
    qDebug()<<ImgUrl;
}

void MainWindow::onRepliedImg(QNetworkReply *replyImg)
{
    qDebug()<<"图片资源请求成功";
    int satus_code = replyImg->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"operation: "<<replyImg->operation();
    qDebug()<<"satus_code: "<<satus_code;
    qDebug()<<"url: "<<replyImg->url();
    qDebug()<<"raw header: "<<replyImg->rawHeaderList();
    if(replyImg->error() != QNetworkReply::NoError ||satus_code != 200 ){
        qDebug()<<replyImg->errorString().toLatin1().data();
        QMessageBox::warning(this,"QtWeather","网络连接失败",QMessageBox::Ok);
    }else{
        //QByteArray byteArray = replyImg->readAll();
        //qDebug()<<"read all:" <<byteArray.data();

//        QPixmap Pixmap;
//        Pixmap.loadFromData(byteArray);
          ByteImg = replyImg->readAll();
            //QString data = QString::fromStdString(ImageData.toStdString());
          //  QPixmap Pixmap;
          //  Pixmap.loadFromData(ImageData);
       //  ui->label_img->setPixmap(Pixmap);
        fromJsonImg(ByteImg);
    }
    replyImg->deleteLater();
}

void MainWindow::fromJsonImg(QByteArray &ByteImg)
{
    //定义QPixmap类 对象
    QPixmap Pixmap;
    //loadFromData方法，
    Pixmap.loadFromData(ByteImg);
    if (Pixmap.loadFromData(ByteImg)) {
    //加载成功，使用pixmap对象
    Pixmap.scaled(this->size(), Qt::KeepAspectRatio);	//设置图片大小为当前窗口大小，并保持横纵比
    ui->label_img->setScaledContents(true);		//设置可以缩放
    ui->label_img->setPixmap(Pixmap);
    } else {
    //加载失败
    qDebug()<<"图片资源加载失败,或者不支持当前图片格式";
    ui->label_img->setText("图片资源加载失败,或者不支持当前图片格式");
    }
}

void MainWindow::on_pushButton_clicked()
{
     fromJsonImg(ByteImg);
     GetNetJson();
     GetNetImgJson(ImgUrl);
}

