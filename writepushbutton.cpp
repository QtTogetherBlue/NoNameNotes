#include "writepushbutton.h"

//myPushButton::myPushButton(QWidget *parent) : QWidget(parent)
//{

//}

//构造函数
writePushButton::writePushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix2;
    bool ret2=pix2.load(normalImg);
    if(ret2){
        //设置图片的固定大小
        this->setFixedSize(pix2.width(),pix2.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix2);

        //设置图标大小
        this->setIconSize(QSize(120,120));
    }
}
