#include "more.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
more::more(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1500,1000);
    this->setWindowTitle("设置");
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::Window); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //返回按钮
    MyPushButton *backbtn=new MyPushButton(":/image/back.png",1,1);
    backbtn->setParent(this);
    // 计算按钮的水平位置，使其水平居中
    int btnWidth = backbtn->width();
    int btnHeight = backbtn->height();
    int x = (this->width() - btnWidth) / 2;
    // 设置按钮的垂直位置，稍微向下偏移
    int y = (this->height()-btnHeight);
    backbtn->move(x, y);

    connect(backbtn,&MyPushButton::clicked,[=]{
        backbtn->zoom1();
        backbtn->zoom2();
        //延时
        QTimer::singleShot(100,this,[=](){
            emit this->moreBack();
        });
    });
}
void more::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/explain.png");
    // 获取窗口大小
        int width = this->width();
        int height = this->height();
        // 绘制图像，使其铺满窗口
        painter.drawPixmap(0, 0, width, height, pix);
}
