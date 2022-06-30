#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit myPushButton(QWidget *parent = 0);


    //构造函数
    myPushButton(QString normalImg,QString pressImg="");
    //成员属性，保存用户传入的默认路径和用户按下后的路径
    QString normalImgPath;
    QString pressImgPath;

    //按下特效
    void zoom1();//向下跳
    void zoom2();//向上跳


signals:

public slots:
};

#endif // MYPUSHBUTTON_H
