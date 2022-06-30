#include"show.h"
#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QMouseEvent>
#include <QMenu>
#include <QPushButton>
#include <QString>

edit::edit()
{
    setWindowFlags(Qt::FramelessWindowHint); // 去标题栏
    this->resize(500,300);
    this->setStyleSheet("background-color: rgb(251, 251, 246); border-color:rgb(148, 145, 123); border-width:6px");
    QVBoxLayout *Vout = new QVBoxLayout; // 三格
    QHBoxLayout *Hout = new QHBoxLayout;

    editTag = new QLineEdit;
    QString stylesheet = "background-color:rgb(255, 181, 54)";
    QString tstring;
    tstring = "border-width:2px;border-style:solid;border-radius:6px; border-color:rgb(52, 147, 223);"
              "background-color:rgb(229, 241, 251);color:rgb(0, 0, 0);";
    tstring.append("font-family:Comic Sans MS;");
    tstring.append("font-size:12pt");
    tstring.append("}"
                      "QPushButton:hover{"
                      "color:rgb(0, 0, 0) border-color:rgb(143, 184, 255); background-color:rgb(195, 223, 251);");
    tstring.append("}");
    tstring.append("QPushButton:pressedQPushButton:pressed{color:rgb(0, 0, 0);"
                   "border-color:rgb(112, 154,255); background-color:rgb(183, 216,251);}");
//    t_doc->setStyleSheet(tstring);
    Delete = new QPushButton;
    Ensure = new QPushButton;
    Cancel = new QPushButton;

    Delete->setFixedHeight(50); Ensure->setFixedHeight(50); Cancel->setFixedHeight(50);

    Delete->setText("Delete");Ensure->setText("Done"); Cancel->setText("Cancel");
    Delete->setStyleSheet(tstring); Ensure->setStyleSheet(tstring); Cancel->setStyleSheet(tstring);

    QFont font;
    font.setPointSize(16);
    font.setFamily(("Comic Sans MS"));
    font.setBold(false);
    editTag->setFont(font);
    editTag->setPlaceholderText("rename:");
    editTag->setClearButtonEnabled(true);

    Hout->addWidget(Delete);
    Hout->addWidget(Cancel);
    Vout->addLayout(Hout);
    Vout->addWidget(editTag, 3);
    Vout->addWidget(Ensure, 1);
    this->setLayout(Vout);

    QObject::connect(Delete, &QPushButton::clicked, this, &edit::emitDelete);
    QObject::connect(Ensure, &QPushButton::clicked, this, &edit::SaveTag);
    QObject::connect(Cancel, &QPushButton::clicked, this, &edit::close);

}

void edit::emitRenew()
{
    emit ok_renew();
}
void edit::emitDelete()
{
    emit ok_delete();
    this->close();
}
void edit::SaveTag()
{
    QFile file("text.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream dataStr(&file);
    dataStr << this->editTag->text();
    file.close();
    this->close();
    emitRenew();
}

//new_edit的函数
new_edit::new_edit()
{
    setWindowFlags(Qt::FramelessWindowHint); // 去标题栏
    this->resize(500,300);
    this->setStyleSheet("background-color: rgb(251, 251, 246); border-color:rgb(148, 145, 123); border-width:6px");
    QVBoxLayout *Vout = new QVBoxLayout; // 三格
    QHBoxLayout *Hout = new QHBoxLayout;

    addTag = new QLineEdit;
    QString stylesheet = "background-color:rgb(255, 181, 54)";
    QString tstring;
    tstring = "border-width:2px;border-style:solid;border-radius:6px; border-color:rgb(52, 147, 223);"
              "background-color:rgb(229, 241, 251);color:rgb(0, 0, 0);";
    tstring.append("font-family:Comic Sans MS;");
    tstring.append("font-size:12pt");
    tstring.append("}"
                      "QPushButton:hover{"
                      "color:rgb(0, 0, 0) border-color:rgb(143, 184, 255); background-color:rgb(195, 223, 251);");
    tstring.append("}");
    tstring.append("QPushButton:pressedQPushButton:pressed{color:rgb(0, 0, 0);"
                   "border-color:rgb(112, 154,255); background-color:rgb(183, 216,251);}");
//    t_doc->setStyleSheet(tstring);
    Ensure = new QPushButton;
    Cancel = new QPushButton;

    Ensure->setFixedHeight(50); Cancel->setFixedHeight(50);

    Ensure->setText("Done"); Cancel->setText("Cancel");
    Ensure->setStyleSheet(tstring); Cancel->setStyleSheet(tstring);

    QFont font;
    font.setPointSize(16);
    font.setFamily(("Comic Sans MS"));
    font.setBold(false);
    addTag->setFont(font);
    addTag->setPlaceholderText("name:");
    addTag->setClearButtonEnabled(true);
    addTag->setClearButtonEnabled(true);

    Vout->addWidget(addTag, 3);
    Hout->addWidget(Cancel);
    Hout->addWidget(Ensure);
    Vout->addLayout(Hout);

    this->setLayout(Vout);


    QObject::connect(Ensure, &QPushButton::clicked, this, &new_edit::Save);
    QObject::connect(Cancel, &QPushButton::clicked, this, &new_edit::close);

}

void new_edit::emitCreate()
{
    emit ok_create();
}

void new_edit::Save()
{
    QFile file("initial.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream dataStr(&file);
    dataStr << this->addTag->text();
    file.close();
    this->close();
    emitCreate();
}

exist::exist()
{
    setWindowFlags(Qt::FramelessWindowHint);
    QVBoxLayout *V = new QVBoxLayout;
    this->resize(300, 200);
    this->setStyleSheet("background-color: rgb(251, 251, 246); border-color:rgb(148, 145, 123); border-width:6px");
    QString tstring;
    tstring = "border-width:2px;border-style:solid;border-radius:6px; border-color:rgb(52, 147, 223);"
              "background-color:rgb(229, 241, 251);color:rgb(0, 0, 0);";
    tstring.append("font-family:Comic Sans MS;");
    tstring.append("font-size:12pt");
    tstring.append("}"
                      "QPushButton:hover{"
                      "color:rgb(0, 0, 0); border-color:rgb(143, 184, 255); background-color:rgb(195, 223, 251);");
    tstring.append("}");
    tstring.append("QPushButton:pressedQPushButton:pressed{color:rgb(0, 0, 0);"
                   "border-color:rgb(112, 154, 255); background-color:rgb(183, 216,251);}");
    OK = new QPushButton;
    OK->setText(QString("OK"));
    OK->setStyleSheet(tstring);

    tip = new QLabel;
    tip->setFrameShape(QFrame::Box);
    tstring =  "background-color: rgb(251, 251, 246); border-color:rgb(176, 172, 166); color:rgb(135, 135, 135)";
    QFont font("Comic Sans MS", 12, QFont::Bold);
    tip->setFont(font);
    tip->setText(QString("file with this name already exists"));
    tip->setStyleSheet(tstring);

    V->addWidget(tip);
    V->addWidget(OK);
    this->setLayout(V);

    QObject::connect(OK, &QPushButton::clicked, this, &exist::close);

}

Empty::Empty()
{
    setWindowFlags(Qt::FramelessWindowHint);
    QVBoxLayout *V = new QVBoxLayout;
    this->resize(300, 200);
    this->setStyleSheet("background-color: rgb(251, 251, 246); border-color:rgb(148, 145, 123); border-width:6px");
    QString tstring;
    tstring = "border-width:2px;border-style:solid;border-radius:6px; border-color:rgb(52, 147, 223);"
              "background-color:rgb(229, 241, 251);color:rgb(0, 0, 0);";
    tstring.append("font-family:Comic Sans MS;");
    tstring.append("font-size:12pt");
    tstring.append("}"
                      "QPushButton:hover{"
                      "color:rgb(0, 0, 0); border-color:rgb(143, 184, 255); background-color:rgb(195, 223, 251);");
    tstring.append("}");
    tstring.append("QPushButton:pressedQPushButton:pressed{color:rgb(0, 0, 0);"
                   "border-color:rgb(112, 154, 255); background-color:rgb(183, 216,251);}");
    OK = new QPushButton;
    OK->setText(QString("OK"));
    OK->setStyleSheet(tstring);

    tip = new QLabel;
    tip->setFrameShape(QFrame::Box);
    tstring =  "background-color: rgb(251, 251, 246); border-color:rgb(176, 172, 166); color:rgb(135, 135, 135)";
    QFont font("Comic Sans MS", 12, QFont::Bold);
    tip->setFont(font);
    tip->setText(QString("Please input a name."));
    tip->setStyleSheet(tstring);

    V->addWidget(tip);
    V->addWidget(OK);
    this->setLayout(V);

    QObject::connect(OK, &QPushButton::clicked, this, &Empty::close);
}

