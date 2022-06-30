#ifndef OTHERPUSHBUTTON_H
#define OTHERPUSHBUTTON_H

#include <QPushButton>

class otherPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit otherPushButton(QWidget *parent = 0);


    //构造函数
    otherPushButton(QString normalImg,QString pressImg="");

    //成员属性
    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:
};

#endif // OTHERPUSHBUTTON_H
