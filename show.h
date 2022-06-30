#ifndef SHOW_H
#define SHOW_H


#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>

class edit : public QDialog
{
     Q_OBJECT
private:
    QPushButton* Delete;
    QLineEdit* editTag;
    QPushButton* Ensure;
    QPushButton* Cancel;
    QString newTag;
public:
    edit(); // construct
    QString renewTag(); // 在主窗口读取输入的信息
    void emitRenew(); // 发送创建信号
    void emitDelete();
    void emitClose();
    void SaveTag(); // 保存信息

signals:
    void ok_renew(); // 信号，新建信息输入完毕
    void ok_delete();
    void ok_close();
};
class new_edit : public QDialog
{
     Q_OBJECT
private:
    QPushButton* Ensure;
    QPushButton* Cancel;
    QLineEdit* addTag;
//   QString newTag;
//   int pos;
public:
    new_edit(); // construct
//   QString renewTag(); // 在主窗口读取输入的信息
//   int renewPos();
    void emitCreate(); // 发送创建信号
//    void emitClose();
    void Save(); // 保存信息

signals:
    void ok_create(); // 信号，新建信息输入完毕
    void ok_close();
};

class exist : public QDialog
{
     Q_OBJECT
private:
    QPushButton* OK;
    QLabel* tip;
public:
    exist();
};
class Empty : public QDialog
{
     Q_OBJECT
private:
    QPushButton* OK;
    QLabel* tip;
public:
    Empty();
};
#endif // SHOW_H
