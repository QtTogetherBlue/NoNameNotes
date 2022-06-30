#include "mypushbutton.h"
#include <QPropertyAnimation>

//myPushButton::myPushButton(QWidget *parent) : QWidget(parent)
//{

//}


//构造函数
myPushButton::myPushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(ret){
        //设置图片的固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        //this->setIconSize((QSize(pix.width(),pix.height())));
        //this->setIconSize(QSize(300,120));
    }
}


void myPushButton::zoom1(){
    //变化特效
    //创建一个动画的对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    //设置变化的时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置变化路径曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();

}

void myPushButton::zoom2(){
    //变化特效
    //创建一个动画的对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    //设置变化的时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置变化路径曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
