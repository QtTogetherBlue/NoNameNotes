#ifndef WRITESCENE_H
#define WRITESCENE_H

#include <QMainWindow>
#include <QWidget>
#include <QWizard>
class QErrorMessage;

class writeScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit writeScene(QWidget *parent = 0);

signals:

public slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    QErrorMessage* errordlg;

    QWizardPage* createPage1();
    QWizardPage* createPage2();
    QWizardPage* createPage3();
};

#endif // WRITESCENE_H
