#ifndef PENCILPUSHBUTTON_H
#define PENCILPUSHBUTTON_H

#include <QPushButton>

class pencilPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit pencilPushButton(QWidget *parent = 0);

    //构造函数
    pencilPushButton(QString normalImg,QString pressImg="");

    //成员属性
    QString normalImgPath;
    QString pressImgPath;


signals:

public slots:
};

#endif // PENCILPUSHBUTTON_H
