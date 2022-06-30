#ifndef ERASER_H
#define ERASER_H

#include <QPushButton>

class eraser : public QPushButton
{
    Q_OBJECT
public:
    //explicit eraser(QWidget *parent = 0);

    //构造函数
    eraser(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:
};

#endif // ERASER_H
