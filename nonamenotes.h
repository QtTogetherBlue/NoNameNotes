#ifndef NONAMENOTES_H
#define NONAMENOTES_H

#include <QWidget>
#include <vector>
#include "folder.h"
#include "time.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QDataStream>
#include <QTextEdit>
#include "show.h"
#include "mainwindow.h"
namespace Ui {
class NoNameNotes;
}

class NoNameNotes : public QWidget
{
    Q_OBJECT

public:
    explicit NoNameNotes(QWidget *parent = 0);
    ~NoNameNotes();
    void show_newEdit(); // 显示新建文档界面
    static int row;
    static int colum;
    clock_t starttime;
//    MainWindow* filewindow;
    edit *dial;
    new_edit *AddBox;
    QPushButton *but;
    QPushButton *lab;
    QString initialTag;
    QString stock;
    exist *warnExist;
    Empty *warnEmpty;
public slots:

private:
    Ui::NoNameNotes *ui;
    vector<Folder*> folders;
    int currentFolderIdx;
    QLabel* rightTitle;
    QVBoxLayout* rightLayout3;
    void createLeft(QVBoxLayout* leftLayout);
    void createRight(QVBoxLayout* rightLayout);
    void showFolders(QVBoxLayout* leftLayout3);
    void showFiles(const vector<File*>& files);
    void readDoc(string folderPath);
    void showExist();
    void showEmpty();

};

#endif // NONAMENOTES_H
