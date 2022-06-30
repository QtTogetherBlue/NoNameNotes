#include "otherscene.h"
#include <QMenuBar>
#include <QPushButton>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>
#include "mainwindow.h"
#include <QMainWindow>



//bool otherScene::saveFile(QString fileName){
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

//bool otherScene::slotSaveAs(){
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

//bool otherScene::SaveIf(){
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

//void otherScene::slotOpen(){
//    if(SaveIf()){
//        QString fileName=QFileDialog::getOpenFileName(this);
//        if(!fileName.isEmpty()){
//            loadFile(fileName);
//        }
//    }
//}

//void otherScene::loadFile(QString fileName){
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

//void otherScene::closeEvent(QCloseEvent *event){
//    if(SaveIf()){
//        event->accept();
//    }
//    else{
//        event->ignore();
//    }
//}



otherScene::otherScene(QWidget *parent) : QWidget(parent)
{

    //场景基本信息
    this->setFixedSize(150,400);
    this->setGeometry(88*20,250,150,400);

    //配置图标
    this->setWindowIcon(QPixmap(":/res2/5.png"));
    this->setWindowTitle("···");
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
    photoBtn->move(this->width()*0,this->height()*0);
    fileBtn->move(this->width()*0,this->height()/5);
    emojiBtn->move(this->width()*0,this->height()*2/5);
    saveBtn->move(this->width()*0,this->height()*3/5);
    saveasBtn->move(this->width()*0,this->height()*4/5);

    //链接函数
    connect(fileBtn,&QPushButton::clicked,[=](){
        QString fileName=QFileDialog::getOpenFileName(this,tr("File"),"D:",tr("*.txt"));
//        //qDebug()<<fileName;
//        QFile file(fileName);
//        //以什么样的方式打开
//        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
//            QByteArray array=file.readAll();
//            QString str(array);
//            qDebug()<<str;
//            file.close();
//        }
    });

//    connect(saveBtn,&QPushButton::clicked,[=](){
//       if(saveIf()) slotSave();
//    });

    //QString path=QFileDialog::getOpenFileName(this,"打开文件",".","*.txt");
    //qDebug()<<path;

}
