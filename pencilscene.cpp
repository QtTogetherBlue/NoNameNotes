#include "pencilscene.h"
#include <QMenuBar>
#include <QPushButton>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>

pencilScene::pencilScene(QWidget *parent) : QMainWindow(parent)
{


    //场景基本信息
    this->setFixedSize(150,320);
    this->setGeometry(100*20,250,150,320);

    //配置图标
    this->setWindowIcon(QPixmap(":/res2/3.png"));

    QPushButton* penBtn=new QPushButton("Pen",this);
    QPushButton* eraseBtn=new QPushButton("Eraser",this);
    QPushButton* colorsBtn=new QPushButton("Color",this);
    QPushButton* lineBtn=new QPushButton("Line",this);
    penBtn->setFixedSize(150,80);
    eraseBtn->setFixedSize(150,80);
    colorsBtn->setFixedSize(150,80);
    lineBtn->setFixedSize(150,80);
    penBtn->move(this->width()*0,this->height()*0);
    eraseBtn->move(this->width()*0,this->height()/4);
    colorsBtn->move(this->width()*0,this->height()/2);
    lineBtn->move(this->width()*0,this->height()*3/4);

}
