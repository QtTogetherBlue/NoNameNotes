#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "writescene.h"
#include "pencilscene.h"
#include "otherscene.h"
#include <QTextEdit>
#include <QLabel>
#include<string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    writeScene* ws=NULL;
    pencilScene* ps=NULL;
    otherScene* os=NULL;
    QTextEdit* edit=NULL;
    QLabel* label1=NULL;
    QLabel* label2=NULL;

    QString currentFile;
    static std::string currentPath;


private:
    Ui::MainWindow *ui;

//重绘事件响应函数
protected:
    void paintEvent(QPaintEvent *event);
    //状态栏更新信息函数
    void renewFunc();

//头文件定义槽
private slots:
    void slotCut();
    void slotCopy();
    void slotPaste();
    void slotRedo();
    void slotUndo();
//保存文件的操作
public:
//    bool SaveIf();
//    bool slotSave();
//    bool slotSaveAs();
//    bool saveFile(QString fileName);
//    void slotOpen();
//    void loadFile(QString fileName);
//    void closeEvent(QCloseEvent *event);
//    void setFileName(QString fileName);
    void changeFont();
    void changeColor();
    void otherShow();
    void TxtOpen();
    QPushButton* photoBtn=NULL;
    QPushButton* fileBtn=NULL;
    QPushButton* emojiBtn=NULL;
    QPushButton* saveBtn=NULL;
    QPushButton* saveasBtn=NULL;
public slots:
    void openFile();
    void saveFile();
    void eraserFunc();
    void colorSelect();
    void fontSelect();
    void undo();
    void undo2();


};

#endif // MAINWINDOW_H
