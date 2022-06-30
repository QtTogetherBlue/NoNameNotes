#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFont>
#include <QPushButton>
#include <QMouseEvent>
#include "mypushbutton.h"
#include <QDebug>
#include "writepushbutton.h"
#include "pencilpushbutton.h"
#include "otherpushbutton.h"
#include <QStatusBar>
#include <QTextEdit>
#include <QDockWidget>
#include <QLabel>
#include <QToolBar>
#include <QMenuBar>
#include <QCursor>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <eraser.h>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include "direct.h"
using namespace std;

string MainWindow::currentPath="";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //配置主场景
    //重置大小
    resize(100*20,70*20);
    this->setFixedSize(100*20,70*20);
    //设置背景颜色
    QPalette palette;
    palette.setColor(QPalette::Window,QColor(255,255,255));
    this->setPalette(palette);

    //设置图标
    setWindowIcon(QIcon(":/res2/7.png"));
    //设置标题
    setWindowTitle("未名笔记");


    //设置file按钮
    myPushButton* Btn=new myPushButton(":/res/2.png");
    Btn->setParent(this);
    //Btn->move(5,5);
    Btn->move(this->width()/400,this->height()/280);
    Btn->setIconSize(QSize(this->width()*3/20,this->height()*3/20));



    connect(Btn,&myPushButton::clicked,[=](){
        //qDebug()<<"dianji ";
        //变化特效
        //Btn->zoom1();Btn->zoom2();
        this->close();
        delete this;//调用析构函数 保存文档
    });



    //设置write按钮
    writePushButton *writeBtn=new writePushButton(":/res2/4.png");
    writeBtn->setParent(this);
    //writeBtn->move(90*20,-40);
    writeBtn->move(this->width()*0.9,-this->height()/35);
    writeBtn->setIconSize(QSize(this->width()*0.06,this->height()*6/70));


    //实例化write的场景
    ws=new writeScene;


    //write按钮的实现
    connect(writeBtn,&writePushButton::clicked,[=](){
        //进入到write场景中
        ws->show();
    });


    //设置pencil按钮
    pencilPushButton*pencilBtn=new pencilPushButton(":/res2/3.png");
    pencilBtn->setParent(this);
    pencilBtn->move(80*20,-40);

    //实例化pencil场景
    ps=new pencilScene;

    //pencil按钮的实现
    connect(pencilBtn,&pencilPushButton::clicked,[=](){
       //进入到pencil场景中
        ps->show();
    });


    //设置other按钮
    otherPushButton*otherBtn=new otherPushButton(":/res4/save.png");
    otherBtn->setParent(this);
    otherBtn->move(35*20,70);
    connect(otherBtn,&QPushButton::clicked,this,&MainWindow::saveFile);

    otherPushButton*otherBtn2=new otherPushButton(":/res4/wenjian.png");
    otherBtn2->setParent(this);
    otherBtn2->move(38*20,70);
    connect(otherBtn2,&QPushButton::clicked,this,&MainWindow::openFile);


    otherPushButton*otherBtn3=new otherPushButton(":/res4/xiangpi.png");
    otherBtn3->setParent(this);
    otherBtn3->move(41*20,70);
    connect(otherBtn3,&QPushButton::clicked,this,&MainWindow::eraserFunc);

    otherPushButton*otherBtn4=new otherPushButton(":/res4/chehui1.png");
    otherBtn4->setParent(this);
    otherBtn4->move(44*20,70);
    connect(otherBtn4,&QPushButton::clicked,this,&MainWindow::undo);

    otherPushButton*otherBtn5=new otherPushButton(":/res4/chehui2.png");
    otherBtn5->setParent(this);
    otherBtn5->move(47*20,70);
    connect(otherBtn5,&QPushButton::clicked,this,&MainWindow::undo2);

    otherPushButton*otherBtn6=new otherPushButton(":/res4/yanse.png");
    otherBtn6->setParent(this);
    otherBtn6->move(50*20,70);
    connect(otherBtn6,&QPushButton::clicked,this,&MainWindow::colorSelect);

    otherPushButton*otherBtn7=new otherPushButton(":/res4/ziti.png");
    otherBtn7->setParent(this);
    otherBtn7->move(53*20,70);
    connect(otherBtn7,&QPushButton::clicked,this,&MainWindow::fontSelect);








    eraser* eraBtn=new eraser(":/res4/save.png");
    eraBtn->setParent(this);
    eraBtn->move(15*20,-60);

    eraser* eraBtn2=new eraser(":/res4/wenjian.png");
    eraBtn2->setParent(this);
    eraBtn2->move(20*20,-60);


    eraser* eraBtn3=new eraser(":/res4/yanse.png");
    eraBtn3->setParent(this);
    //eraBtn3->setFixedSize(QSize(95,100));
    eraBtn3->move(25*20,-60);

    eraser* eraBtn4=new eraser(":/res4/xiangpi.png");
    eraBtn4->setParent(this);
    eraBtn4->move(30*20,-85);

    connect(eraBtn3,&QPushButton::clicked,[=](){
       QColorDialog::getColor(Qt::red,this,tr("Color"));
    });
    connect(eraBtn2,&QPushButton::clicked,[=](){
        bool ok;
        QFont font=QFontDialog::getFont(&ok,this);
    });

    //实例化other场景
    os=new otherScene;

    //other按钮的实现
    connect(otherBtn,&otherPushButton::clicked,[=](){
       //进入到other场景中
        //os->show();
        QPushButton* photoBtn=new QPushButton("Photo",this);
        QPushButton* fileBtn=new QPushButton("File",this);
        QPushButton* emojiBtn=new QPushButton("Emoji",this);
        QPushButton* saveBtn=new QPushButton("Save",this);
        QPushButton* saveasBtn=new QPushButton("Save as",this);
        photoBtn->setFixedSize(150,80);
        fileBtn->setFixedSize(150,80);
        emojiBtn->setFixedSize(150,80);
        saveBtn->setFixedSize(150,80);
        saveasBtn->setFixedSize(150,80);
        photoBtn->move(100,50);
        fileBtn->move(150,100);
        emojiBtn->move(200,150);
        saveBtn->move(250,200);
        saveasBtn->move(300,250);
    });



    //设置状态栏
    QStatusBar* stBar=statusBar();
    //放置到主编辑窗口中
    setStatusBar(stBar);
    //放置一些标签控件
    label1=new QLabel("Line：0 || Row：0",this);
    //QLabel* label3=new QLabel("Row",this);
    //将标签放置到状态栏中
    stBar->addWidget(label1);//放到左侧
    //stBar->addWidget(label3);
    label2=new QLabel("Count",this);
    stBar->addPermanentWidget(label2);


//    //菜单栏只能最多有一个
//    //创建菜单栏
//    QMenuBar * bar =menuBar();
//    //将栏目放到窗口中
//    setMenuBar(bar);
//    //创建菜单
//    QMenu* fileMenu=bar ->addMenu("File");
//    QMenu* startMenu=bar->addMenu("Start");
//    QMenu* editMenu=bar->addMenu("Edit");
//    QMenu* plusMenu=bar->addMenu("Add");

//    //创建菜单项之File
//    QAction* newAction= fileMenu->addAction("New");
//    //添加分隔线
//    fileMenu->addSeparator();
//    QAction* openAction=fileMenu->addAction("Open");
//    QAction* closeAction=fileMenu->addAction("Close");
//    //创建菜单项之Add
//    QAction* photoAction=plusMenu->addAction("Photo");
//    QAction* emojiAction=plusMenu->addAction("Emoji");
//    //创建菜单项之Edit
//    QAction* colorAction=editMenu->addAction("Color");
//    QAction* selectAction=editMenu->addAction("Select");

//    //工具栏 可以有多个
//    QToolBar* toolBar=new QToolBar(this);
//    addToolBar(Qt::TopToolBarArea,toolBar);

//    //后期设置，允许左右停放
//    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);

//    //设置浮动操作
//    toolBar->setFloatable(false);

//    //设置移动(总开关)
//    toolBar->setMovable(false);


//    //工具栏中设置内容
//      //
//    photoAction=fileMenu->addAction("Photo");
//    toolBar->addAction(photoAction);
//    toolBar->addSeparator();//添加分割线
//    emojiAction=fileMenu->addAction("Emoji");
//    toolBar->addAction(emojiAction);
//    colorAction=fileMenu->addAction("Color");
//    toolBar->addAction(colorAction);
//    selectAction=fileMenu->addAction("Select");
//    toolBar->addAction(selectAction);

//    //工具栏中添加控件
//    QPushButton* btn=new QPushButton("aa",this);
//    toolBar->addWidget(btn);





    //设置浮动窗口
    QDockWidget* dockWidget1=new QDockWidget("scratch paper",this);
    //放置到中心窗口中
    addDockWidget(Qt::BottomDockWidgetArea,dockWidget1);
    //设置停靠区域
    dockWidget1->setAllowedAreas(Qt::BottomDockWidgetArea);

    //设置文本编辑器
    edit=new QTextEdit(this);
    edit->setFont(QFont("Comic Sans MS",24));//设置默认字体和字体大小
    edit->move(0,130);
    edit->setFixedSize(100*20,60*20);//设置文本编辑界面的大小和位置
    //setCentralWidget(edit);


    //创建文件对象
    QString path=QString::fromStdString(currentPath);
    QFile file(path);
    //打开文件
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QString str(file.readAll());
        edit->setText(str);
        file.close();
    }

    //获取文本框中的内容
//    QString strText=edit->toPlainText();
//    qDebug()<<strText;

    //状态栏更新连接函数
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(renewFunc()));

}

MainWindow::~MainWindow()
{
    QString path=QString::fromStdString(currentPath);
    cout<<"~"<<currentPath<<endl;
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QString str=edit->toPlainText();
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<str<<endl;
        //file.write(str.toLocal8Bit());
        edit->setText("");
        file.close();
    }
    delete ui;
}
void MainWindow::openFile(){
    QString path=QFileDialog::getOpenFileName(this,"Open",".","*.txt *.docx");
//    qDebug()<<path;
    if(path.isEmpty()){
        qDebug()<<"fail!";
    }
    else{
        //创建文件对象
        QFile file(path);
        //打开文件
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QString str(file.readAll());
            edit->setText(str);
            file.close();
        }
    }
}

void MainWindow::saveFile(){
    QString path=QFileDialog::getSaveFileName(this,"Open",".","*.txt *.docx");
    if(path.isEmpty()){
        qDebug()<<"Fail!";
    }
    else{
        QFile file(path);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QString str=edit->toPlainText();
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out<<str<<endl;
            //file.write(str.toLocal8Bit());
            edit->setText("");
            file.close();
        }
    }
}

void MainWindow::eraserFunc(){
    edit->setText("");
}

void MainWindow::colorSelect(){
    QColor col=QColorDialog::getColor(Qt::red,this,tr("Color"));
    edit->setTextColor(col);
}
void MainWindow::fontSelect(){
    bool ok;
    QFont fon=QFontDialog::getFont(&ok,this);
    edit->setFont(fon);
}

void MainWindow::undo(){
    if(!edit->document()->isEmpty()){
        edit->undo();
    }
}
void MainWindow::undo2(){
    if(!edit->document()->isEmpty()){
        edit->redo();
    }
}

//绘图事件函数
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //创建画笔
    QPen pen1(Qt::black);
    painter.setPen(pen1);
    pen1.setWidth(3);
    painter.drawLine(0,130,100*20,130);
    QPen pen2(Qt::gray);
    painter.setPen(pen2);
    painter.drawEllipse(10*20,-50,50,50);
}


//状态栏更新信息函数
void MainWindow::renewFunc(){
    //获取鼠标光标
    QTextCursor textCursor=edit->textCursor();
    int line=textCursor.blockNumber();//获取行数
    int row=textCursor.columnNumber();//获取列数
    label1->setText(tr("Line：%1||Row：%2").arg(line+1).arg(row+1));//更新行数和列数

}




//文本编辑实现函数
void MainWindow::slotCut(){
    edit->cut();
}

void MainWindow::slotCopy(){
    edit->copy();
}

void MainWindow::slotPaste(){
    edit->paste();
}

void MainWindow::slotRedo(){
    edit->redo();
}

void MainWindow::slotUndo(){
    edit->undo();
}

void MainWindow::changeFont(){
    QFontDialog fontDlg;
    QFont font;
    bool ok;
    font=fontDlg.getFont(&ok);
    if(ok) edit->setFont(font);
}


void MainWindow::changeColor(){
    QColorDialog colorDlg;
    QColor color;

    QPalette palette=edit->palette();

    color=colorDlg.getColor(Qt::black);
    if(color.isValid()){
        palette.setColor(QPalette::Text,color);
        edit->setPalette(palette);
    }
}

void MainWindow::otherShow(){
    photoBtn=new QPushButton("Photo",this);
    fileBtn=new QPushButton("File",this);
    emojiBtn=new QPushButton("Emoji",this);
    saveBtn=new QPushButton("Save",this);
    saveasBtn=new QPushButton("Save as",this);
    photoBtn->setFixedSize(150,80);
    fileBtn->setFixedSize(150,80);
    emojiBtn->setFixedSize(150,80);
    saveBtn->setFixedSize(150,80);
    saveasBtn->setFixedSize(150,80);
    photoBtn->move(this->width()*0,this->height()*0);
    fileBtn->move(this->width()*0,this->height()/5);
    emojiBtn->move(this->width()*0,this->height()*2/5);
    saveBtn->move(this->width()*0,this->height()*3/5);
    saveasBtn->move(this->width()*0,this->height()*4/5);
}



//void MainWindow::setFileName(QString fileName){
//    currentFile=fileName;
//    edit->document()->setModified(false);
//    this->setWindowModified(false);
//    fileName.isEmpty()?
//                this->setWindowFilePath("new/txt"):
//                this->setWindowFilePath(fileName);

//}


//bool MainWindow::saveFile(QString fileName){
//    QFile file(fileName);
//    if(!file.open(QFile::WriteOnly|QFile::Text)){
//        QMessageBox::critical(this,"critical","cannot write file");
//        return false;
//    }
//    else{
//        QTextStream out(&file);
//        out<<edit->toPlainText();
//        setFileName(fileName);
//        return true;
//    }
//}

//bool MainWindow::slotSaveAs(){
//    QString fileName=QFileDialog::getSaveFileName(this,tr("Save AS"),"/home/mary",tr("Text Files(*.txt"));
//    if(fileName.isEmpty()){
//        return false;
//    }
//    else return saveFile(fileName);
//}

//bool MainWindow::slotSave(){
//    if(currentFile.isEmpty()){
//        return slotSaveAs();
//    }
//    else{
//        return saveFile(currentFile);
//    }
//}

//bool MainWindow::SaveIf(){
//    if(edit->document()->isModified()){
//        //如果文件被修改了
//        QMessageBox::StandardButtons res;
//        res=QMessageBox::warning(this,"!","是否保存文件？",QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);

//        if(res==QMessageBox::Cancel) return false;//不保存
//        else if(res==QMessageBox::Save) return slotSave();
//        else if(res==QMessageBox::Discard) return true;
//    }
//    else return true;
//}

//void MainWindow::slotOpen(){
//    if(SaveIf()){
//        QString fileName=QFileDialog::getOpenFileName(this);
//        if(!fileName.isEmpty()){
//            loadFile(fileName);
//        }
//    }
//}

//void MainWindow::loadFile(QString fileName){
//    QFile file(fileName);
//    if(!file.open(QFile::ReadOnly|QFile::Text)){
//        QMessageBox::critical(this,"critical","can't read file");
//    }
//    else{
//        QTextStream in(&file);
//        edit->setText(in.readAll());
//        setFileName(fileName);
//    }
//}

//void MainWindow::closeEvent(QCloseEvent *event){
//    if(SaveIf()){
//        event->accept();
//    }
//    else{
//        event->ignore();
//    }
//}

