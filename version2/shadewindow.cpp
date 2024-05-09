#include "shadewindow.h"

shadewindow::shadewindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1500,1000);
    this->setPalette(Qt::black);
    this->setWindowOpacity(0);//设置窗口透明度
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏
}
