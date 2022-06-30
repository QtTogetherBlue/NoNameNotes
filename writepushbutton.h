#ifndef WRITEPUSHBUTTON_H
#define WRITEPUSHBUTTON_H

#include <QPushButton>

class writePushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit writePushButton(QWidget *parent = 0);

    //构造函数
    writePushButton(QString normalImg,QString pressImg="");
    //成员属性
    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:
};

#endif // WRITEPUSHBUTTON_H
