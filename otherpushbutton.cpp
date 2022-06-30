#include "otherpushbutton.h"

//otherPushButton::otherPushButton(QWidget *parent) : QWidget(parent)
//{

//}


//构造函数
otherPushButton::otherPushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix4;
    bool ret4=pix4.load(normalImg);
    if(ret4){
        //设置图片固定大小
        this->setFixedSize(pix4.width(),pix4.height());
        //this->setFixedSize(160,160);

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix4);

        //设置图标大小
        this->setIconSize(QSize(160,160));
    }
}
