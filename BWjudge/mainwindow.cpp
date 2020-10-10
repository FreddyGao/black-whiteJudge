#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#include <QDebug>
#include<QPaintEvent>
#include<QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button=new QPushButton("开始游戏",this);
    button->setGeometry(300,500,200,50);
    connect(button,SIGNAL(clicked()),this,SLOT(slotStart()));
    connect(&this->n,&num::Mysignal,this,&MainWindow::dealSlot);
}
void MainWindow::slotStart(){
    if(button->text()=="开始游戏"){
    n.show();}


}
void MainWindow::dealSlot(int x){
    if(button->text()=="开始游戏"){
    this->n.hide();
    this->setUNum(x);
    voteBox *voBox=new voteBox(x);
    int totalNum=this->getUNum();
    if(totalNum%2==0)this->setCaptainVoteNum(1.5);
    else {
        this->setCaptainVoteNum(0.5);
    }
    users* userChain=new users(totalNum,totalNum,0);
    user* head=userChain->createUserList(totalNum);
    this->setHead(head);
    this->setUserChain(userChain);
    this->userChain->setDay(true);
    this->userChain->setVoteBox(voBox);
    button->setText("开始村长竞选");
    update();
    connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked()),Qt::UniqueConnection);
    }
}
void MainWindow:: on_Button_clicked(){

    if(button->text()=="开始村长竞选"){
        this->getUserChain()->setHaveDonePeople(0);
        head=this->getHead();
        user* now=head->right;
        this->userChain->sts=1;
        this->userChain->t1=now->num;
        update();
        this->getUserChain()->setNowPosition(now);
        this->getUserChain()->setHaveDonePeople(1);
        button->setText("下一位");
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_2()),Qt::UniqueConnection);
        }

}
void MainWindow::on_Button_clicked_2(){
    if(button->text()=="下一位"){
        int a=this->getUserChain()->getHaveDonePeople();
        int b=this->getUserChain()->getNowPeople();
        if(a==b){
            button->setText("开始村长投票");

            this->getUserChain()->setNowPosition(this->getHead());
            this->getUserChain()->setHaveDonePeople(0);

            connect(&this->v,&vote::Mysignal_2,this,&MainWindow::dealSlot_2);
            connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_2()));
        }
        else {
            int now=this->userChain->getHaveDonePeople();
            int sum=now;
            user* nowP=this->head;
            nowP=nowP->right;
            while (sum!=0) {
                nowP=nowP->right;
                sum--;
            }
            this->userChain->t1=nowP->num;
            update();

            this->getUserChain()->setHaveDonePeople(this->getUserChain()->getHaveDonePeople()+1);


}}
    if(button->text()=="开始村长投票"){
        v.show();
        this->userChain->voteSts=false;
        connect(&this->v,&vote::Mysignal_2,this,&MainWindow::dealSlot_2);
    }
    if(button->text()=="开始放逐投票"){
        v.show();
        this->userChain->voteSts=true;
        connect(&this->v,&vote::Mysignal_2,this,&MainWindow::dealSlot_2);
    }
}
void MainWindow::dealSlot_2(int num){
    if(button->text()=="开始村长投票"){
    this->v.hide();
    this->userChain->setHaveDonePeople(0);
    head=this->getHead();
    user* now=head->right;
    this->userChain->sts=2;
    this->userChain->t1=now->num;
    this->userChain->t2=num;
    update();
    this->userChain->getVoteBox()->clearVoteBox();
    userChain->getVoteBox()->vote(num,0,0);
    this->getUserChain()->setHaveDonePeople(1);
    v.hide();
    button->setText("下一位投票");
    connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_3()),Qt::UniqueConnection);
    }
    if(button->text()=="开始放逐投票"){
        this->v.hide();
        this->userChain->setHaveDonePeople(0);
        head=this->getHead();
        user* now=head->right;
        this->userChain->getVoteBox()->clearVoteBox();
        qDebug()<<now->num<<"号玩家";
        qDebug()<<num;
        this->userChain->getVoteBox()->clearVoteBox();
        if(now->num==this->userChain->getCaptainNum()){
            this->userChain->getVoteBox()->vote(num,this->captainVoteNum,true);
        }
        else {
            this->userChain->getVoteBox()->vote(num,this->captainVoteNum,false);
        }
        button->setText("下一位投票");
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_3()),Qt::UniqueConnection);
    }
}
void MainWindow::on_Button_clicked_3(){

        v.show();
        connect(&this->v,&vote::Mysignal_2,this,&MainWindow::dealSlot_3,Qt::UniqueConnection);


}
void MainWindow::dealSlot_3(int num){
    if(this->userChain->voteSts==false){
        if(!this->userChain->voteSts){
        int now=this->userChain->getHaveDonePeople();
        int sum=now;
        v.hide();
        if(now!=this->userChain->getNowPeople()){
        user* nowP=this->head;
        nowP=nowP->right;
        while (sum!=0) {
            nowP=nowP->right;
            sum--;
        }
        userChain->getVoteBox()->vote(num,0,0);
        this->userChain->t1=nowP->num;
        this->userChain->t2=num;
        this->getUserChain()->setHaveDonePeople(this->getUserChain()->getHaveDonePeople()+1);
    }
        if(now==this->userChain->getNowPeople()){
            int *captain=userChain->getVoteBox()->maxNUmUser();
            int captainNum=captain[0];
            userChain->setCaptainNum(captainNum);
            this->userChain->sts=3;
            this->userChain->t1=captainNum;
            this->userChain->setCaptainNum(captainNum);
            update();
            button->setText("下面请警长决定发言顺序");
            this->userChain->setHaveDonePeople(0);
            connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_4()));
        }
    }
        else {
            int now=this->userChain->getHaveDonePeople();
            int sum=now;
            v.hide();
            if(now!=this->userChain->getNowPeople()){
            user* nowP=this->head;
            nowP=nowP->right;
            while (sum!=0) {
                nowP=nowP->right;
                sum--;
            }
            if(nowP->num==this->userChain->getCaptainNum()){
                this->userChain->getVoteBox()->vote(num,this->captainVoteNum,true);
            }
            else {
                this->userChain->getVoteBox()->vote(num,this->captainVoteNum,false);
            }
            button->setText("下一位投票");
        }
            if(now==this->userChain->getNowPeople()){
                qDebug()<<666;
            }
}}}
void MainWindow::on_Button_clicked_4(){
    this->userChain->setDay(true);
    this->userChain->d.show();
    connect(&this->userChain->d,&dir::Mysignal,this,&MainWindow::dealSlot_4,Qt::UniqueConnection);

}
void MainWindow::dealSlot_4(int num){
    this->userChain->d.hide();
    if(num==1){
        this->userChain->sts=4;
        this->userChain->t1=1;
        update();
        this->userChain->setDir(true);
        this->userChain->d.hide();
        user* nowP=this->userChain->findCaptainPosition(this->getHead());
        int now=this->userChain->getHaveDonePeople();
        int sum=now;
        nowP=nowP->right;
        while (sum!=0) {
            nowP=nowP->right;
            sum--;
        }
        this->userChain->sts=5;
        this->userChain->t1=nowP->num;
        button->setText("下一位玩家");
        update();
        this->userChain->setHaveDonePeople(this->userChain->getHaveDonePeople()+1);
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_5()),Qt::UniqueConnection);
    }
    if(num==0){
        this->userChain->sts=4;
        this->userChain->t1=0;
        update();
        this->userChain->setDir(false);
        this->userChain->d.hide();
        user* nowP=this->userChain->findCaptainPosition(this->getHead());
        int now=this->userChain->getHaveDonePeople();
        int sum=now;
        nowP=nowP->left;
        while (sum!=0) {
            nowP=nowP->left;
            sum--;
        }
        this->userChain->sts=5;
        this->userChain->t1=nowP->num;
        update();
        button->setText("下一位玩家");
        this->userChain->setHaveDonePeople(this->userChain->getHaveDonePeople()+1);
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_5()),Qt::UniqueConnection);
    }
}
void MainWindow::on_Button_clicked_5(){
    this->userChain->d.hide();
    int a=this->userChain->getNowPeople();
    int b=this->userChain->getHaveDonePeople();
    if(a==b){
        button->setText("开始放逐投票");
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_2()),Qt::UniqueConnection);
    }
    else {
        if(this->userChain->getDir()){
        this->userChain->d.hide();
        user* nowP=this->userChain->findCaptainPosition(this->getHead());
        int now=this->userChain->getHaveDonePeople();
        int sum=now;
        nowP=nowP->right;
        while (sum!=0) {
            nowP=nowP->right;
            sum--;
        }
        this->userChain->sts=5;
        this->userChain->t1=nowP->num;
        update();
        button->setText("下一位玩家");
        this->userChain->setHaveDonePeople(this->userChain->getHaveDonePeople()+1);
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_5()),Qt::UniqueConnection);
    }
    else {
        this->userChain->d.hide();
        user* nowP=this->userChain->findCaptainPosition(this->getHead());
        int now=this->userChain->getHaveDonePeople();
        int sum=now;
        nowP=nowP->left;
        while (sum!=0) {
            nowP=nowP->left;
            sum--;
        }
        this->userChain->sts=5;
        this->userChain->t1=nowP->num;
        update();
        button->setText("下一位玩家");
        this->userChain->setHaveDonePeople(this->userChain->getHaveDonePeople()+1);
        connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_5()),Qt::UniqueConnection);
    }}
}
/*void MainWindow::on_Button_clicked_6(){
    this->userChain->v2.show();
    connect(&this->userChain->v2,&vote_2::Mysignal_2,this,&MainWindow::dealSlot_5,Qt::UniqueConnection);
}
void MainWindow::dealSlot_5(int num){

   this->userChain->v2.hide();
   disconnect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_6()));
   this->userChain->setHaveDonePeople(0);
   head=this->getHead();
   user* now=head->right;
   this->userChain->getVoteBox()->clearVoteBox();
   qDebug()<<now->num<<"号玩家";
   qDebug()<<num;
   this->userChain->getVoteBox()->clearVoteBox();
   if(now->num==this->userChain->getCaptainNum()){
       this->userChain->getVoteBox()->vote(num,this->captainVoteNum,true);
   }
   else {
       this->userChain->getVoteBox()->vote(num,this->captainVoteNum,false);
   }
   button->setText("下一位投票");
   connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_7()),Qt::UniqueConnection);
}
void MainWindow::on_Button_clicked_7(){
    int now=this->userChain->getHaveDonePeople();
    if(now<this->userChain->getNowPeople())
    v.show();
    connect(&this->v,&vote::Mysignal_2,this,&MainWindow::dealSlot_6);
}
void MainWindow::dealSlot_6(int num){
    v.hide();
    int b=this->userChain->getNowPeople();
    int now=this->userChain->getHaveDonePeople();
    int sum=now;
    if(now!=b){
         user* nowP=this->head;
         nowP=nowP->right;
         while (sum!=0) {
            nowP=nowP->right;
            sum--;
           }
         qDebug()<<nowP->num<<"号玩家:";
         qDebug()<<num;
         if(nowP->num==this->userChain->getCaptainNum()){
             this->userChain->getVoteBox()->vote(num,this->captainVoteNum,true);
         }
         else {
             this->userChain->getVoteBox()->vote(num,this->captainVoteNum,false);
         }
         this->userChain->setHaveDonePeople(now+1);
         //connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_7()),Qt::UniqueConnection);
}
    if(now==b){
                   int *exileP=userChain->getVoteBox()->maxNUmUser();
                   int ePerson=exileP[0];
                   this->userChain->sts=6;
                   this->userChain->t1=ePerson;
                   user* h=this->userChain->deleteUser(ePerson,this->getHead());
                   this->setHead(h);
                   if(ePerson==this->userChain->getCaptainNum()){
                       this->userChain->c.show();
                       connect(&this->userChain->c,&choose::Mysignal,this,&MainWindow::dealSlot_7);
                   }
                   else {
                       this->button->setText("进入夜晚");
                       disconnect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_7()));
                       connect(button,SIGNAL(clicked()),this,SLOT( on_Button_clicked_8()));}

    }
}
void MainWindow::dealSlot_7(int num){
    this->userChain->c.hide();
    this->userChain->setCaptainNum(num);
    this->button->setText("进入夜晚");
    qDebug()<<num<<"新队长";
    disconnect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_7()));
    connect(button,SIGNAL(clicked()),this,SLOT( on_Button_clicked_8()));
}
void MainWindow::on_Button_clicked_8(){
    this->userChain->setUserEyeStatus(this->getHead());
    this->userChain->setDay(false);
    srand((int)time(NULL));
    bool night=rand()%2;
    this->userChain->setNight(night);
    if(night){
        int redEyeOpenNum=userChain->looUpRedEyeStatus(head);
            if(redEyeOpenNum%2==0)captainVoteNum=1;
    }
    else {
        int redEyeOpenNum=userChain->lookUpBlackEyeStatus(head);
           if(redEyeOpenNum%2==0)captainVoteNum=1;
    }
    update();
    button->setText("进入白天");
    disconnect(button,SIGNAL(clicked()),this,SLOT( on_Button_clicked_8()));
    connect(button,SIGNAL(clicked()),this,SLOT(on_Button_clicked_4()));
}
*/

void MainWindow::paintEvent(QPaintEvent *){
    if(this->head==nullptr)return;
    QPainter p(this);
        p.setBrush(Qt::blue);
        p.setFont(QFont("微软雅黑",20,700,false));
    int num=this->userChain->getTotalPeople();
                    p.setBrush(Qt::blue);
                    p.drawRect(300,200,100,100);
                    p.setPen(Qt::black);
                    p.setFont(QFont("微软雅黑",10,700,false));
                    //在方块中 绘制Text， 并且文本位置位于中部
                    if(this->userChain->sts==1){
                        int a=this->userChain->t1;

                        p.drawText(QRectF(300,200,100,100),QString::number(a)+"号玩家发言",QTextOption(Qt::AlignCenter));
                    }
                    if(this->userChain->sts==2){
                        int a=this->userChain->t1;
                        int b=this->userChain->t2;
                        p.drawText(QRectF(300,200,100,100),QString::number(a)+"号玩家的投票结果:"+QString::number(b),QTextOption(Qt::AlignCenter));
                    }
                    if(this->userChain->sts==3){
                        int a=this->userChain->t1;
                        p.drawText(QRectF(300,200,100,100),QString::number(a)+"号玩家当选警长",QTextOption(Qt::AlignCenter));
                    }
                    if(this->userChain->sts==4){
                        int a=this->userChain->t1;
                        if(a==0)p.drawText(QRectF(300,200,100,100),"左边发言",QTextOption(Qt::AlignCenter));
                        else {
                            p.drawText(QRectF(300,200,100,100),"右边发言",QTextOption(Qt::AlignCenter));
                        }
                    }
                    if(this->userChain->sts==5){
                        int a=this->userChain->t1;
                         p.drawText(QRectF(300,200,100,100),QString::number(a)+"号玩家发言",QTextOption(Qt::AlignCenter));
                    }
                    if(this->userChain->sts==6){
                        int a=this->userChain->t1;
                         p.drawText(QRectF(300,200,100,100),QString::number(a)+"号玩家被放逐",QTextOption(Qt::AlignCenter));
                    }

    for(int i=0;i<num;i++){
        p.setBrush(Qt::red);
                        p.drawRect(60,i*60+40,55,55);
                        p.setPen(Qt::black);
                        p.setFont(QFont("微软雅黑",10,700,false));
                        //在方块中 绘制Text， 并且文本位置位于中部
                        p.drawText(QRectF(60,i*60+40,55,55),QString::number(i+1)+"号玩家",QTextOption(Qt::AlignCenter));
                        if(this->userChain->checkUserStatus(i+1)==false)
                            p.drawText(QRectF(60,i*60+50,55,55),"已被驱逐",QTextOption(Qt::AlignCenter));
                        if(this->userChain->getCaptainNum()==i+1&&this->userChain->checkUserStatus(this->userChain->getCaptainNum()))
                            p.drawText(QRectF(60,i*60+50,55,55),"村长",QTextOption(Qt::AlignCenter));
                        if(this->userChain->getDay()==false&&this->userChain->checkUserStatus(i+1)==true){
                                user*pp=this->userChain->findPeoplePosition(i+1,this->head);
                                bool eye=pp->eyeStatus;
                                if(eye){
                                   p.drawText(QRectF(55,i*60+25,55,55),"睁眼",QTextOption(Qt::AlignCenter));
                                }
                                else {
                                    p.drawText(QRectF(55,i*60+25,55,55),"闭眼",QTextOption(Qt::AlignCenter));
                                }
                        }

    }}

void MainWindow::setUNum(int n){
    this->uNUm=n;
}
int MainWindow::getUNum(){
    return this->uNUm;
}
float MainWindow::getCaptainVoteNum(){
    return this->captainVoteNum;
}
void MainWindow::setCaptainVoteNum(float captainVoteNum){
    this->captainVoteNum=captainVoteNum;
}
void MainWindow::setHead(user *head){
    this->head=head;
}
user* MainWindow::getHead(){
    return this->head;
}
users* MainWindow::getUserChain(){
    return this->userChain;

}
void MainWindow::setUserChain(users *userChain){
    this->userChain=userChain;
}
MainWindow::~MainWindow()
{
    delete ui;
}
