#include "pencilpushbutton.h"

//pencilPushButton::pencilPushButton(QWidget *parent) : QWidget(parent)
//{

//}

//构造函数
pencilPushButton::pencilPushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix3;
    bool ret3=pix3.load(normalImg);
    if(ret3){
        //设置图片的固定大小
        this->setFixedSize(pix3.width(),pix3.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix3);

        //设置图标大小
        this->setIconSize(QSize(120,120));
    }
}
