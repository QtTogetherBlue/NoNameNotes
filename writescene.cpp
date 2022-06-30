#include "writescene.h"
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

writeScene::writeScene(QWidget *parent) : QMainWindow(parent)
{

    //配置场景基本信息
    this->setFixedSize(150,160);
    this->setGeometry(110*20,250,150,160);

    //配置图标
    this->setWindowIcon(QPixmap(":/res2/4.png"));

    //设置标题
    this->setWindowTitle("write");

    //创建菜单栏
    //QMenuBar * bar=menuBar();
    //setMenuBar(bar);

    //创建菜单
    //QMenu * startMenu = bar->addMenu("Start");

    //创建退出菜单栏
    //QAction* quitAction=startMenu->addAction("exit");

    //信号链接
//    connect(quitAction,&QAction::triggered,[=](){
//        this->close();
//    });


    QPushButton* colorBtn=new QPushButton("Color",this);
    //QPushButton* sizeBtn=new QPushButton("Size",this);
    QPushButton* fontBtn=new QPushButton("Font",this);
    colorBtn->setFixedSize(150,80);
    //sizeBtn->setFixedSize(150,80);
    fontBtn->setFixedSize(150,80);

    colorBtn->move(this->width()*0,this->height()*0);
    //sizeBtn->move(this->width()*0,this->height()/3);
    fontBtn->move(this->width()*0,this->height()/2);

    //链接函数---颜色对话框
    connect(colorBtn,&QPushButton::clicked,[=](){
       QColorDialog::getColor(Qt::red,this,tr("Color"));
    });

    //链接函数---字体对话框
    connect(fontBtn,&QPushButton::clicked,[=](){
       bool ok;
       QFont font=QFontDialog::getFont(&ok,this);
    });



}
//颜色对话框
void writeScene::on_pushButton_1_clicked(){
    QColorDialog dialog(Qt::red, this);                // 创建对象
    dialog.setOption(QColorDialog::ShowAlphaChannel); // 显示alpha选项
    dialog.exec();                                    // 以模态方式运行对话框
    QColor color = dialog.currentColor();             // 获取当前颜色
}
//大小对话框
void writeScene::on_pushButton_2_clicked(){

}
//字体对话框
void writeScene::on_pushButton_3_clicked(){
    bool ok;//ok 用来记录是否点击了ok 的按钮
    QFont font=QFontDialog::getFont(&ok,this);
    //if(ok)
}

