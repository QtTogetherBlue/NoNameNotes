#include "eraser.h"

//eraser::eraser(QWidget *parent) : QWidget(parent)
//{

//}


eraser::eraser(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix5;
    bool ret5=pix5.load(normalImg);
    if(ret5){
        this->setFixedSize(pix5.width(),pix5.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix5);
        this->setIconSize(QSize(pix5.width(),pix5.height()));
    }
}
