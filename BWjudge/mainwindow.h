#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include <QLineEdit>
#include <QMessageBox>
//#include "inputnumwindow.h"
#include "num.h"
#include "users.h"
#include <QDebug>
#include<QPaintEvent>
#include<QPainter>
#include<vote.h>
#include<votebox.h>
#include<dir.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setUNum(int n);
    int getUNum();
    void setCaptainVoteNum(float captainVoteNum);
    float getCaptainVoteNum();
    void setHead(user* head);
    user* getHead();
    void setUserChain(users* userChain);
    users* getUserChain();
    void paintEvent(QPaintEvent *);

    MainWindow(int a);
    ~MainWindow();
public slots:
    void slotStart();
    void dealSlot(int num);
    void dealSlot_2(int num);
    void dealSlot_3(int num);
    void dealSlot_4(int num);
    //void dealSlot_5(int num);
    //void dealSlot_6(int num);
    //void dealSlot_7(int num);
    void on_Button_clicked();
    void on_Button_clicked_2();
    void on_Button_clicked_3();
    void on_Button_clicked_4();
    void on_Button_clicked_5();
    //void on_Button_clicked_6();
    //void on_Button_clicked_7();
    //void on_Button_clicked_8();
private:
    Ui::MainWindow *ui;
        num n;
        vote v;
        int uNUm;
        float captainVoteNum;
        user* head;
        users* userChain;
        QPushButton *button;
};

#endif // MAINWINDOW_H
