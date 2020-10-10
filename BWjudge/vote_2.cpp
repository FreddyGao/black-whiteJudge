#include "vote_2.h"

vote_2::vote_2(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(300,300);
    edit=new QLineEdit();
    edit->show();
    edit->setPlaceholderText("请输入放逐投票结果");
    edit->move(50,50);
    edit->setFixedSize(100,10);
    edit->setParent(this);

    QPushButton *button;
    button=new QPushButton("确定",this);
    button->setGeometry(200,100,50,50);

    connect(button,SIGNAL(clicked()),this,SLOT(sendSlot_2()));
}
void vote_2:: sendSlot_2(){
    int num=this->edit->text().toInt();
    this->n=num;
    //this->hide();
    emit Mysignal_2(this->n);

}
