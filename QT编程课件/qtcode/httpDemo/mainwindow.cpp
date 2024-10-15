#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NetAccessManager = new QNetworkAccessManager(this);//用以访问接口
    ImgNetAccessManager = new QNetworkAccessManager(this);//用以访问图片数据

    connect(NetAccessManager,&QNetworkAccessManager::finished,this,&MainWindow::onReplied);//访问接口
    connect(ImgNetAccessManager,&QNetworkAccessManager::finished,this,&MainWindow::onRepliedImg);//访问图片



    GetNetJson();
    GetNetImgJson(ImgUrl);

   // setWindowFlag(Qt::FramelessWindowHint); //设置无边框
    setFixedSize(width(),height());     //设置固定当前窗口大小

    //演示阅读文档
    QWidget* btn = new QPushButton("新增");
    ui->toolBox->addItem(btn,"新按钮");

    if(1 == 1){
        ui->toolBox->setItemEnabled(1,false);
    }

    // ui->toolBox.
}

MainWindow::~MainWindow()
{
    delete ui;
}
//http 网络请求
void MainWindow::GetNetJson()
{
    QUrl url("https://api.thecatapi.com/v1/images/search?size=full");
    NetAccessManager->get(QNetworkRequest(url));//获取成功 触发信号，调用对应的槽函数   ，  发送请求
}


void MainWindow::GetNetImgJson(QString url)
{
    ImgNetAccessManager->get(QNetworkRequest(url));//获取指定图片链接成功  则会调用   对应的槽函数
}

//获取json数据，其中包含图片url readall 存在byteArr中
//最后调用fromjson 解析出qstring imgurl ，   这是请求json数据时的槽函数
void MainWindow::onReplied(QNetworkReply *reply)
{

    qDebug()<<"发起网络请求";
    int satus_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"operation: "<<reply->operation();
    qDebug()<<"satus_code: "<<satus_code;
    qDebug()<<"url: "<<reply->url();
    qDebug()<<"raw header: "<<reply->rawHeaderList();
    if(reply->error() != QNetworkReply::NoError ||satus_code != 200 ){
        qDebug()<<reply->errorString().toLatin1().data();
        QMessageBox::warning(this,"QtNet","网络连接失败",QMessageBox::Ok);
    }else{
        QByteArray byteArray = reply->readAll();
        qDebug()<<"read all:" <<byteArray.data();

        //QPixmap Pixmap;
        //Pixmap.loadFromData(byteArray);
        fromNetJson(byteArray);  //处理解析获取到的JSON数据
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
    QJsonDocument doc = QJsonDocument::fromJson(byteArr.data());//将返回的字符串转换为对象
    if(!doc.isArray()){
        qDebug()<<"拿到的数据不是一个 jsonArray!";
        return;
    }
    qDebug() << "doc[0]" << doc[0];
    //2.开始解析
    QJsonValue objVal = doc.array().at(0);//获取数组第一个元素数据
    QJsonObject obj = objVal.toObject();//转换为对象模式
    ImgUrl = obj.value("url").toString();//获取其中的图片地址并赋值给成员变量
    qDebug()<< "ImgUrl:" <<ImgUrl;
    GetNetImgJson(ImgUrl);//根据返回的图片地址获取图片，特别是在刚打开时需要刷最新的图到界面

}

void MainWindow::onRepliedImg(QNetworkReply *replyImg)
{
    qDebug()<<"开始请求图片资源";
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
        fromJsonImg(ByteImg);//根据返回的图片数据渲染图片区
    }
    replyImg->deleteLater();
}

void MainWindow::fromJsonImg(QByteArray &ByteImg)//根据获取的图片数据渲染图片区域
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
    //加载慢的时候先显示文字
    qDebug()<<"图片正在加载...";
    ui->label_img->setText("图片正在加载...");
    }
}

void MainWindow::on_pushButton_clicked()
{
    GetNetJson();
    GetNetImgJson(ImgUrl);
}

