#include "nonamenotes.h"
#include "mainwindow.h"
#include "ui_nonamenotes.h"

#include <QPushButton>
#include "folder.h"
#include "file.h"
#include <vector>
#include <QLayout>
#include <string>
#include <QFrame>
#include <Qstring>
#include <QLineEdit>
#include <QAction>
#include <QLabel>
#include <direct.h>
#include <io.h>
#include <QMessageBox>
#include <QMenu>
#include<iostream>
#include<fstream>
#include "windows.h"
#include "show.h"
using namespace std;
NoNameNotes::NoNameNotes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoNameNotes)
{
    ui->setupUi(this);

    resize(34*36,21*36);
    //设置背景颜色
    QPalette palette;
    palette.setColor(QPalette::Window,QColor(255, 255, 255));
    this->setPalette(palette);
    setWindowIcon(QIcon(":/res2/7.png"));

    //建立布局
    QHBoxLayout* mainLayout=new QHBoxLayout(this);
    QVBoxLayout* leftLayout=new QVBoxLayout(this);
    QVBoxLayout* rightLayout=new QVBoxLayout(this);

    currentFolderIdx=-1;

    createLeft(leftLayout);
    createRight(rightLayout);

    QFrame* vline=new QFrame();
    vline->setFrameShape(QFrame::VLine);
    vline->setStyleSheet("QFrame{background-color:grey;min-width:5px}");



//    QGroupBox *upBox = createRight();
//    QGroupBox *downBox = createShowBox();
//    setMouseTracking(true);
//    rightLayout->addWidget(upBox, 5);
//    rightLayout->addWidget(downBox, 2);



    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(vline);
    mainLayout->addLayout(rightLayout);
    //设置各部分占比
    mainLayout->setStretch(0,2);
    mainLayout->setStretch(1,1);
    mainLayout->setStretch(2,8);

    //this->setContextMenuPolicy(Qt::CustomContextMenu);
}

NoNameNotes::~NoNameNotes()
{
    delete ui;
}
void NoNameNotes::createLeft(QVBoxLayout* leftLayout)
{
    QVBoxLayout* leftLayout1=new QVBoxLayout(this);
    QHBoxLayout* leftLayout2=new QHBoxLayout(this);
    QVBoxLayout* leftLayout3=new QVBoxLayout(this);
    QVBoxLayout* leftLayout4=new QVBoxLayout(this);

    leftLayout->addLayout(leftLayout1);
    leftLayout->addLayout(leftLayout2);
    leftLayout->addLayout(leftLayout3);
    leftLayout->addLayout(leftLayout4);

    //搜索框
    QFont font;
    font.setPointSize(14);
    font.setFamily(("Comic Sans MS"));
    font.setBold(false);
    QLineEdit* search_edit = new QLineEdit(this);
    search_edit->setFixedHeight(50);
    search_edit->setFont(font);
    search_edit->setPlaceholderText("Search");
    search_edit->setClearButtonEnabled(true);
    leftLayout2->addWidget(search_edit);

    //+按钮
    QPushButton* plusButton=new QPushButton;

    plusButton->setFixedSize(100,100);
    plusButton->setText("");
    QPixmap pixmap(":/buttons/addbutton.png");
    QPixmap fitpixmap = pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    plusButton->setIcon(QIcon(fitpixmap));
    plusButton->setIconSize(QSize(70, 70));
    plusButton->setFlat(true);
    plusButton->setStyleSheet("border: 0px");

    leftLayout4->addWidget(plusButton);

    connect(plusButton, &QPushButton::clicked, this, [=]()
    {
        AddBox = new new_edit;
        connect(AddBox, &new_edit::ok_create, this, [=]()
        {
            QFile file("initial.txt");
            file.open(QIODevice::ReadOnly);
            QDataStream dataStr(&file);
            while(!dataStr.atEnd())
                dataStr >> initialTag;
            file.close();

            string newname=initialTag.toStdString();
            if(newname=="")
            {
                showEmpty();
                return;
            }
            for(auto fo:folders)
                if(fo->getName()==newname)
                {
                    showExist();
                    return;
                }
            auto f=new Folder(newname);
            mkdir(("_doc/"+newname).c_str());
            folders.push_back(f);

            QPushButton* button=new QPushButton(f->getName().c_str());
            button->setFixedHeight(60);

            QString styleSheet="QPushButton{"
                               "color:";
            styleSheet.append((f->getColor()+";").c_str());
            styleSheet.append("font-family:Comic Sans MS;");
            styleSheet.append("font-size:24pt;");
            styleSheet.append("border-radius:20px;");
            styleSheet.append(("border:3px solid "+f->getColor()+";").c_str());

            styleSheet.append("}"
                              "QPushButton:hover{"
                              "color:#ffffff;");
            styleSheet.append(("background-color:"+f->getColor()+";").c_str());
            styleSheet.append("}");
            button->setStyleSheet(styleSheet);
            connect(button, &QPushButton::pressed, this, [=]()
            {
                starttime=clock();
            });
            connect(button,&QPushButton::released,this,[=]()
            {

                if((clock()-starttime)/CLOCKS_PER_SEC>0.4)//长按(大于0.4秒)
                {
                    dial = new edit;
                    connect(dial, &edit::ok_renew, this, [=]()
                    {
                        QFile file("text.txt");
                        file.open(QIODevice::ReadOnly);
                        QDataStream dataStr(&file);
                        while(!dataStr.atEnd())
                            dataStr >> stock;
                        file.close();
                        string newname = "";
                        newname = stock.toStdString();
                        string temp = f->getName();
                        if(newname == "")
                        {
                            showEmpty();
                            return;
                        }
                        f->setName("");
                        for(auto fo:folders)
                            if(fo->getName()==newname)
                            {
                                showExist();
                                f->setName(temp);
                                return;
                            }
                        f->setName(temp);
                        button->setText(stock);
                        rename(("_doc/"+f->getName()).c_str(),("_doc/"+newname).c_str());
                        f->setName(newname);
                    });
                    connect(dial, &edit::ok_delete, this, [=]()
                    {
                        for(auto it=folders.begin();it!=folders.end();it++)
                        {
                            if((*it)->getName()==f->getName())
                            {
                                for(auto fi:f->files)
                                    remove(("_doc/"+f->getName()+"/"+fi->getName()+".txt").c_str());
                                folders.erase(it);
                                break;
                            }
                        }
                        rmdir(("_doc/"+f->getName()).c_str());
                        delete button;
                    });
                    dial->exec();
                }
                else//单击
                {
                    //            cout<<f->getName()<<endl;
                                currentFolderIdx=folders.size()-1;
                                for(int i=0;i<folders.size();i++)
                                    if(folders[i]->getName()==f->getName())
                                    {
                                        currentFolderIdx=i;
                                        break;
                                    }
                                rightTitle->setText(QString::fromStdString(f->getName()));
                                showFiles(f->files);
                }
            });
            leftLayout3->addWidget(button);
        });
        AddBox->exec();
    });

    //标题
    QLabel* title=new QLabel(this);
    title->setFixedSize(280, 65);
    title->setText("");
    QImage Weiming(":/buttons/weimingbiji.png");
    QPixmap t_wm = QPixmap::fromImage(Weiming);
    QPixmap fitWeiming = t_wm.scaled(280, 65, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    title->setPixmap(fitWeiming);
    title->setStyleSheet("border: 0px");

    leftLayout1->addWidget(title);


    //搜索按钮
    QPushButton* search_btn=new QPushButton(this);
    search_btn->setFixedHeight(40);
    search_btn->setIcon(QIcon(":/res/search.png"));
    leftLayout2->addWidget(search_btn);
    connect(search_btn,&QPushButton::clicked,[=]()
    {
        string search_str=search_edit->text().toStdString();
//        cout<<search_str<<endl;
        //先清空所有按钮
        QLayoutItem* child;
        while((child=leftLayout3->takeAt(0))!=0)
        {
            if(child->widget())
                child->widget()->setParent(NULL);
            delete child;
        }
        //找到搜索结果显示出来
        int i=0;
        for(auto it=folders.begin();it!=folders.end();it++)
        {
            if((*it)->getName().find(search_str)!=string::npos)
            {
                auto f=*it;
                QPushButton* button=new QPushButton(f->getName().c_str());
                button->setFixedHeight(60);

                QString styleSheet="QPushButton{"
                                   "color:";
                styleSheet.append((f->getColor()+";").c_str());
                styleSheet.append("font-family:Comic Sans MS;");
                styleSheet.append("font-size:24pt;");
                styleSheet.append("border-radius:20px;");
                styleSheet.append(("border:3px solid "+f->getColor()+";").c_str());

                styleSheet.append("}"
                                  "QPushButton:hover{"
                                  "color:#ffffff;");
                styleSheet.append(("background-color:"+f->getColor()+";").c_str());
                styleSheet.append("}");
                button->setStyleSheet(styleSheet);
                connect(button, &QPushButton::pressed, this, [=]()
                {
                    starttime=clock();
                });
                connect(button,&QPushButton::released,this,[=]()
                {

                    if((clock()-starttime)/CLOCKS_PER_SEC>0.4)//长按(大于0.4秒)
                    {
                        dial = new edit;
                        connect(dial, &edit::ok_renew, this, [=]()
                        {
                            QFile file("text.txt");
                            file.open(QIODevice::ReadOnly);
                            QDataStream dataStr(&file);
                            while(!dataStr.atEnd())
                                dataStr >> stock;
                            file.close();
                            string newname = "";
                            newname = stock.toStdString();
                            string temp = f->getName();
                            if(newname == "")
                            {
                                showEmpty();
                                return;
                            }
                            f->setName("");
                            for(auto fo:folders)
                                if(fo->getName()==newname)
                                {
                                    showExist();
                                    f->setName(temp);
                                    return;
                                }
                            f->setName(temp);
                            button->setText(stock);
                            newname=stock.toStdString();
                            rename(("_doc/"+f->getName()).c_str(),("_doc/"+newname).c_str());
                            f->setName(newname);
                        });
                        connect(dial, &edit::ok_delete, this, [=]()
                        {
                            for(auto it=folders.begin();it!=folders.end();it++)
                            {
                                if((*it)->getName()==f->getName())
                                {
                                    for(auto fi:f->files)
                                        remove(("_doc/"+f->getName()+"/"+fi->getName()+".txt").c_str());
                                    folders.erase(it);
                                    break;
                                }
                            }
                            rmdir(("_doc/"+f->getName()).c_str());
                            delete button;
                        });
                        dial->exec();
                    }
                    else//单击
                    {
                        //            cout<<f->getName()<<endl;
                        currentFolderIdx=i;
                        rightTitle->setText(QString::fromStdString(f->getName()));
                        showFiles(f->files);
                    }
                });
                leftLayout3->addWidget(button);
            }
            i++;
        }
    });


    readDoc("_doc");
    showFolders(leftLayout3);
}

void NoNameNotes::createRight(QVBoxLayout* rightLayout)
{
    QVBoxLayout* rightLayout1=new QVBoxLayout(this);
    QHBoxLayout* rightLayout2=new QHBoxLayout(this);
    rightLayout3=new QVBoxLayout(this);
    QVBoxLayout* rightLayout4=new QVBoxLayout(this);

    rightLayout->addLayout(rightLayout1);
    rightLayout->addLayout(rightLayout2);
    rightLayout->addLayout(rightLayout3);
    rightLayout->addLayout(rightLayout4);


/*
    QFont font;
    font.setPointSize(16);
    font.setFamily(("Comic Sans MS"));
    font.setBold(false);
    addTag->setFont(font);
    addTag->setPlaceholderText("file's name:");
    addTag->setClearButtonEnabled(true);
*/
    //搜索框
    QFont font;
    font.setPointSize(14);
    font.setFamily(("Comic Sans MS"));
    font.setBold(false);
    QLineEdit* search_edit = new QLineEdit(this);
    search_edit->setFixedHeight(50);
    search_edit->setFont(font);
    search_edit->setPlaceholderText("Search");
    search_edit->setClearButtonEnabled(true);
    rightLayout2->addWidget(search_edit);


    //+按钮
    QPushButton* plusButton=new QPushButton;

    plusButton->setFixedSize(100,100);
    plusButton->setText("");
    QPixmap pixmap(":/buttons/addbutton.png");
    QPixmap fitpixmap = pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    plusButton->setIcon(QIcon(fitpixmap));
    plusButton->setIconSize(QSize(70, 70));
    plusButton->setFlat(true);
    plusButton->setStyleSheet("border: 0px");

    rightLayout4->addWidget(plusButton);

    connect(plusButton, &QPushButton::clicked, this, [=]()
    {
        if(currentFolderIdx==-1)
            return;
        AddBox = new new_edit;
        connect(AddBox, &new_edit::ok_create, this, [=]()
        {
            QFile file("initial.txt");
            file.open(QIODevice::ReadOnly);
            QDataStream dataStr(&file);
            while(!dataStr.atEnd())
                dataStr >> initialTag;
            file.close();
            string newname=initialTag.toStdString();
            //不能为空
            if(newname=="")
            {
                showEmpty();
                return;
            }
            //判断是否已有
            for(auto fo:folders[currentFolderIdx]->files)
                if(fo->getName()==newname)
                {
                    showExist();
                    return;
                }
            //新建
            auto f=new File(newname);
//            cout<<"fff"<<f->getName()<<endl;
            //mkdir(("_doc/"+folders[currentFolderIdx]->getName()+"/").c_str());
            ofstream fout("_doc/"+folders[currentFolderIdx]->getName()+"/"+newname+".txt",ios::out);
            folders[currentFolderIdx]->files.push_back(f);

            showFiles(folders[currentFolderIdx]->files);
        });
        AddBox->exec();
    });

//    showFiles();
    //标题
    rightTitle=new QLabel(this);
//    rightTitle->setFixedSize(300, 80);
    rightTitle->adjustSize();
    rightTitle->setText("Files");

    QString styleSheet2="QLabel{"
                       "color:";
    styleSheet2.append("#000000;");
    styleSheet2.append("font-family:Comic Sans MS;");
    styleSheet2.append("font-size:24pt;");
    styleSheet2.append("}");
    rightTitle->setStyleSheet(styleSheet2);

    rightLayout1->addWidget(rightTitle);


    //搜索按钮
    QPushButton* search_btn=new QPushButton(this);
    search_btn->setFixedHeight(40);
    search_btn->setIcon(QIcon(":/res/search.png"));
    rightLayout2->addWidget(search_btn);
    connect(search_btn,&QPushButton::clicked,[=]()
    {
        if(currentFolderIdx==-1)
            return;
        string search_str=search_edit->text().toStdString();
//        cout<<search_str<<endl;
        //找到搜索结果显示出来
        vector<File*> searchfiles;
        for(auto it=folders[currentFolderIdx]->files.begin();it!=folders[currentFolderIdx]->files.end();it++)
            if((*it)->getName().find(search_str)!=string::npos)
                searchfiles.push_back(*it);
        showFiles(searchfiles);
    });
}

void NoNameNotes::readDoc(string folderPath)
{
    if (0 != access(folderPath.c_str(), 0))
        mkdir(folderPath.c_str());
    long   hFile = 0;
    struct _finddata_t fileinfo;  //很少用的文件信息读取结构
    string p;
    if ((hFile = _findfirst(p.assign(folderPath).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib &  _A_SUBDIR))  //是文件夹
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
//                    cout<<p.assign(fileinfo.name)<<endl;
                    folders.push_back(new Folder(p.assign(fileinfo.name)));
                    readDoc(folderPath+"/"+folders.back()->getName());
                }
            }
            else
            {
//                cout<<p.assign(fileinfo.name)<<endl;
                folders.back()->files.push_back(new File(p.assign(string(fileinfo.name).substr(0,string(fileinfo.name).length()-4))));
            }
        }while(_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void NoNameNotes::showFolders(QVBoxLayout* leftLayout3)
{
    for(int i=0;i<folders.size();i++)
    {
        auto f=folders[i];
        QPushButton* button=new QPushButton(f->getName().c_str());
        button->setFixedHeight(60);

        QString styleSheet="QPushButton{"
                           "color:";
        styleSheet.append((f->getColor()+";").c_str());
        styleSheet.append("font-family:Comic Sans MS;");
        styleSheet.append("font-size:24pt;");
        styleSheet.append("border-radius:20px;");
        styleSheet.append(("border:3px solid "+f->getColor()+";").c_str());

        styleSheet.append("}"
                          "QPushButton:hover{"
                          "color:#ffffff;");
        styleSheet.append(("background-color:"+f->getColor()+";").c_str());
        styleSheet.append("}");
        button->setStyleSheet(styleSheet);
        connect(button, &QPushButton::pressed, this, [=]()
        {
            starttime=clock();
        });
        connect(button,&QPushButton::released,this,[=]()
        {
            if((clock()-starttime)/CLOCKS_PER_SEC>0.4)//长按(大于0.4秒)
            {
                dial = new edit;
                connect(dial, &edit::ok_renew, this, [=]()
                {
                    QFile file("text.txt");
                    file.open(QIODevice::ReadOnly);
                    QDataStream dataStr(&file);
                    while(!dataStr.atEnd())
                        dataStr >> stock;
                    file.close();
                    string s = "";
                    s = stock.toStdString();
                    string temp = f->getName();
                    if(s == "")
                    {
                        showEmpty();
                        return;
                    }
                    f->setName("");
                    for(auto fo:folders)
                        if(fo->getName()==s)
                        {
                            showExist();
                            f->setName(temp);
                            return;
                        }
                    f->setName(temp);
                    button->setText(stock);
                    string newname=stock.toStdString();
                    rename(("_doc/"+f->getName()).c_str(),("_doc/"+newname).c_str());
                    f->setName(newname);
                });
                connect(dial, &edit::ok_delete, this, [=]()
                {
                    for(auto it=folders.begin();it!=folders.end();it++)
                    {
                        if((*it)->getName()==f->getName())
                        {
                            for(auto fi:f->files)
                                remove(("_doc/"+f->getName()+"/"+fi->getName()+".txt").c_str());
                            folders.erase(it);
                            break;
                        }
                    }
                    rmdir(("_doc/"+f->getName()).c_str());
                    delete button;
                });
                dial->exec();
            }
            else//单击
            {
                //            cout<<f->getName()<<endl;
                            currentFolderIdx=i;
                            rightTitle->setText(QString::fromStdString(f->getName()));
                            showFiles(f->files);
            }
        });
        leftLayout3->addWidget(button);
    }
    leftLayout3->setSpacing(20);//间隙
    leftLayout3->setAlignment(Qt::AlignTop);//靠上而不是均匀分布
}
void NoNameNotes::showFiles(const vector<File*>& files)
{
    //清空每个layout里的pushbutton
    QLayoutItem* child;
    while((child=rightLayout3->takeAt(0))!=0)
    {
        if(child->layout())
        {
            QLayoutItem* childchild;
            while((childchild=child->layout()->takeAt(0))!=0)
            {
                if(childchild->widget())
                    childchild->widget()->setParent(NULL);
                delete childchild;
            }
            child->layout()->setParent(NULL);
        }
        delete child;
    }

    //cout<<"showFiles "<<currentFolderIdx<<endl;
    if(currentFolderIdx==-1||files.size()==0)
        return;

    int rowNum=(files.size()-1)/3+1;
    for(int i=0;i<rowNum;i++)
    {
        QHBoxLayout* row=new QHBoxLayout(this);
        rightLayout3->addLayout(row);
        for(int j=i*3;j<min(i*3+3,(int)files.size());j++)
        {
            auto f=files[j];
            QPushButton* button=new QPushButton(f->getName().c_str());
            button->setFixedHeight(120);
            button->setFixedWidth(300);
            QString styleSheet="QPushButton{"
                               "color:";
            styleSheet.append((folders[currentFolderIdx]->getColor()+";").c_str());
            styleSheet.append("font-family:Comic Sans MS;");
            styleSheet.append("font-size:24pt;");
            styleSheet.append("border-radius:20px;");
            styleSheet.append(("border:3px solid "+folders[currentFolderIdx]->getColor()+";").c_str());

            styleSheet.append("}"
                              "QPushButton:hover{"
                              "color:#ffffff;");
            styleSheet.append(("background-color:"+folders[currentFolderIdx]->getColor()+";").c_str());
            styleSheet.append("}");
            button->setStyleSheet(styleSheet);
            connect(button, &QPushButton::pressed, this, [=]()
            {
                starttime=clock();
            });
            connect(button,&QPushButton::released,this,[=]()
            {
                if((clock()-starttime)/CLOCKS_PER_SEC>0.4)//长按(大于0.4秒)
                {
                    dial = new edit;
                    connect(dial, &edit::ok_renew, this, [=]()//重命名
                    {
                        QFile file("text.txt");
                        file.open(QIODevice::ReadOnly);
                        QDataStream dataStr(&file);
                        while(!dataStr.atEnd())
                            dataStr >> stock;
                        file.close();
                        string newname = "";
                        newname = stock.toStdString();
                        cout<<"-----------"<<endl;
                        cout<<newname<<endl;
                        cout<<" -------------------"<<endl;
                        string temp = f->getName();
                        if(newname == "")
                        {
                            showEmpty();
                            return;
                        }
                        f->setName("");
                        for(auto fo:folders[currentFolderIdx]->files)
                            if(fo->getName()==newname)
                            {
                                showExist();
                                f->setName(temp);
                                return;
                            }
                        f->setName(temp);
                        button->setText(stock);
                        rename(("_doc/"+folders[currentFolderIdx]->getName()+"/"+f->getName()+".txt").c_str(),("_doc/"+folders[currentFolderIdx]->getName()+"/"+newname+".txt").c_str());
                        f->setName(newname);
                    });
                    connect(dial, &edit::ok_delete, this, [=]()//删除
                    {
                        for(auto it=folders[currentFolderIdx]->files.begin();it!=folders[currentFolderIdx]->files.end();it++)
                        {
                            if((*it)->getName()==f->getName())
                            {
                                folders[currentFolderIdx]->files.erase(it);
                                //cout<<f->getName()<<folders[currentFolderIdx].size()<<endl;
                                break;
                            }
                        }
                        remove(("_doc/"+folders[currentFolderIdx]->getName()+"/"+f->getName()+".txt").c_str());

                        delete button;
                    });
                    dial->exec();
                }
                else//单击
                {
                    //todo
                    MainWindow::currentPath="_doc/"+folders[currentFolderIdx]->getName()+"/"+f->getName()+".txt";
                    MainWindow* filewindow=new MainWindow();
                    cout<<filewindow->currentPath<<endl;
                    filewindow->setWindowTitle(QObject::tr("未名笔记"));
                    filewindow->show();
                }
            });
            row->addWidget(button);
        }
        row->setSpacing(20);//间隙
        row->setAlignment(Qt::AlignLeft);//靠上而不是均匀分布
    }

    rightLayout3->setSpacing(20);//间隙
    rightLayout3->setAlignment(Qt::AlignTop);//靠上而不是均匀分布
}



void NoNameNotes::showExist()
{
    warnExist = new exist;
    warnExist->exec();
}

void NoNameNotes::showEmpty()
{
    warnEmpty = new Empty;
    warnEmpty->exec();
}
