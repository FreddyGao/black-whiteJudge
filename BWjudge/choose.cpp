#include "choose.h"

choose::choose(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(300,300);
    edit=new QLineEdit();
    edit->show();
    edit->setPlaceholderText("请选择你的继承人");
    edit->move(50,50);
    edit->setFixedSize(100,10);
    edit->setParent(this);

    QPushButton *button;
    button=new QPushButton("确定",this);
    button->setGeometry(200,100,50,50);

    connect(button,SIGNAL(clicked()),this,SLOT(sendSlot()));
}
void choose:: sendSlot(){
    int num=this->edit->text().toInt();
    this->n=num;
    emit Mysignal(this->n);
}
