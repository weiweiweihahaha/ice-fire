#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<QTimer>
#include<QSound>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(2000,1500);
    this->setWindowIcon(QPixmap(":/image/min.jpg"));
    this->setWindowTitle("森林冰火人");

    //设置遮罩
    shade = new shadewindow;
    shade->setParent(this,Qt::FramelessWindowHint | Qt::Window);
    shade->setGeometry(0, 0, this->width(), this->height());
    shade->hide();

    //播放音乐
    QSound *startSound=new QSound(":/image/LevelMusic.wav",this);
    startSound->play();
    startSound->setLoops(100);//循环一百次

    //开始按钮
    MyPushButton *startbtn=new MyPushButton(":/image/play2.png",0.7,0.7);
    startbtn->setParent(this);
   // startbtn->move(this->width()*0.5-startbtn->width()*0.5,250);
    int btnWidth = startbtn->width();
    int btnHeight = startbtn->height();
    int x = (this->width() - btnWidth) / 2;
    // 设置按钮的垂直位置，稍微向下偏移
    int y = (this->height()-btnHeight);
    startbtn->move(x, y);

    gam=new game;

    connect(startbtn,&MyPushButton::clicked,[=](){

        startbtn->zoom1();
        startbtn->zoom2();
        //延时
        QTimer::singleShot(100,this,[=](){
            gam->reset();
            this->hide();
            gam->show();
        });
    });

    //set button
    se=new set;
    MyPushButton *setbtn=new MyPushButton(":/image/set-removebg-preview.png",0.4,0.4);
    setbtn->setParent(this);
    setbtn->move(this->width()-200,1250);
    connect(se,&set::setBack,this,[=](){
        se->hide();
        shade->hide();
    });
    connect(se,&set::stopmusic,this,[=](){
        startSound->stop();
    });
    connect(se,&set::playmusic,this,[=](){
        startSound->play();
        startSound->setLoops(100);
    });
    connect(setbtn,&MyPushButton::clicked,[=](){
        setbtn->zoom1();
        setbtn->zoom2();
        se->show();
        shade->show();
    });
    //questionButton
    mo=new more;
    MyPushButton *questionbtn=new MyPushButton(":/image/more-removebg-preview.png",0.4,0.4);
    questionbtn->setParent(this);
    questionbtn->move(-110,1200);
    connect(mo,&more::moreBack,this,[=](){
        mo->hide();
        shade->hide();
    });
    connect(questionbtn,&MyPushButton::clicked,[=](){
        questionbtn->zoom1();
        questionbtn->zoom2();
        mo->show();
        shade->show();
    });
    //winend
    win=new winend;
    connect(gam,&game::winend1,[=](){
        shade->show();
        win->show();
    });
    connect(win,&winend::CloseWinend,[=](){
       gam->reset();
       gam->hide();
       win->close();
       shade->hide();
       this->show();
    });
    //winend2
    win2=new winend2;
    connect(gam,&game::winend2,[=](){
        shade->show();
        win2->show();
    });
    connect(win2,&winend2::CloseWinend2,[=](){
       gam->reset();
       gam->hide();
       win2->close();
       shade->hide();
       this->show();
    });
    //loseend
    lose=new loseend;
    connect(gam,&game::loseend1,[=](){
        //qDebug()<<"66666666666";
        shade->show();
        lose->show();
    });
    connect(lose,&loseend::menus,[=](){
       gam->reset();
       gam->hide();
       lose->hide();
       shade->hide();
       this->show();
    });
    connect(lose,&loseend::retrys,[=](){
       gam->reset();
       lose->hide();
       shade->hide();
    });
}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/start.png");
    int width = this->width();
    int height = this->height();
    // 绘制图像，使其铺满窗口
    painter.drawPixmap(0, 0, width, height, pix);
}
MainWindow::~MainWindow()
{
    delete ui;
}

