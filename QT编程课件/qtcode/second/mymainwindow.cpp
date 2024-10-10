#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    //创建一个工具栏，   如果默认有工具栏，被封装到  ui下
    QToolBar* fileToolBar = new QToolBar("文件工具栏",this);
    this->addToolBar(fileToolBar);
    fileToolBar->addAction(ui->actionOpen);
    //创建一个保存action
    QAction* saveAction = new QAction("&Save");
    // saveAction->setShortcuts()
    fileToolBar->addAction(saveAction);
    ui->menuFile_F->addAction(saveAction);

    //触发open   Action  弹出   文件对话框
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::on_action_Close_triggered()
{
    this->close();
}


void MyMainWindow::on_actionOpen_triggered()
{
    //弹出打开文件的标准对话框
    QString fname = QFileDialog::getOpenFileName(this,"打开文本文件","C:/IAR","文本文件(*txt *html)");
    //qDebug() << fname;
    if(!fname.isEmpty()){//选择了文件
        //open   read    write
        QFile file(fname);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this,"出错了","您可能没有权限");
        }else{
            QTextStream in(&file);
            QString content = in.readAll();
            ui->textEdit->setText(content);
            file.close();
        }
    }else{
        QMessageBox::information(this,"出错了","您未选择文件");
    }
}

