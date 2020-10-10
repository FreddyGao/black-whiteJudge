//
// Created by 高飞 on 2020/9/7.
//
#include <stdlib.h>
#include <time.h>
#include "users.h"
void users:: setNight(bool night){
    this->night=night;
}
bool users::getNight(){
    return this->night;
}
user* users::findPeoplePosition(int num,user*head){
    user*p=head->right;
   for(int i=0;i<this->getNowPeople();i++){
         if(p->num==num){
             return p;}
         else {
             p=p->right;
         }
    }
   return nullptr;


}
bool users::getDay(){
    return this->day;
}
void users::setDay(bool day){
    this->day=day;}
voteBox* users::getVoteBox(){
    return this->vBox;
}
int users:: getTotalPeople(){
    return this->totalPeople;
}
void users::setVoteBox(voteBox *voteBox){
    this->vBox=voteBox;
}
void users::setDir(bool dir){
    this->dirct=dir;
}
bool users::getDir(){
    return this->dirct;
}
user* users::createUserList(int totalPeople) {
   int userNum[totalPeople];
   this->totalPeople=totalPeople;
    srand((int)time(NULL));
    this->userIdentity= reinterpret_cast<bool *>(new bool *[totalPeople]);
    for(int i=0;i<totalPeople;i++){
        userNum[i]=1+rand()%totalPeople;
        for(int j=0;j<i;j++){
            if(userNum[i]==userNum[j]){i--;break;}
        }

    }
    this->userStatus=new int[totalPeople];
    for(int i=0;i<totalPeople;i++){
        this->userStatus[i]= true;
        this->userIdentity[i]=userNum[i]%2;
        if(this->userIdentity[i])redNum++;
        else blackNum++;
        this->userStatus[i]= true;
    }
    user *pUser;
    user *nUser;
    user *head = new user;
    int redNum,blackNum;
    for(int i=0;i<totalPeople;i++){
        user *newUser;
        newUser=new user;
        newUser->num=i+1;

        if(i==0){
        head->right=newUser;}
        else{
            pUser->right=newUser;
            newUser->left=pUser;
            if(i==totalPeople-1){
                pUser->right=newUser;
                newUser->right=head->right;
                head->right->left=newUser;
                newUser->left=pUser;
                return head;
            }}
            pUser=newUser;}
    this->redNum=redNum;
    this->blackNum=blackNum;
}
user* users::deleteUser(int num,user* head) {
    this->userStatus[num-1]= false;
    bool id=this->userIdentity[num-1];
    if(id){
        this->setRedNum(this->getRedNum()-1);
    } else{
        this->setRedNum(this->getBlackNum()-1);
    }
    this->setNowPeople(this->getNowPeople()-1);
    if(head->right->num==num){
        user* p;
        user* q;
        p=head->right;
        head->right=p->right;
        head->right->left=p->left;
        q=p->left;
        q->right=p->right;
        delete p;
    } else{
        user *p;
        p=head->right;
        while (p->num!=num){
            p=p->right;
            if(p->right==head)return head;
        }
        p->left->right=p->right;
        p->right->left=p->left;
        delete p;
    }
    return head;
}
users::users(int totalNum,int nowNum,int captainNum){
    this->captainNum=captainNum;
    this->nowPeople=nowNum;
    this->totalPeople=totalNum;
}
void users::setNowPeople(int nowPeople) {
    this->nowPeople=nowPeople;
}
void users::setCaptainNum(int CaptainNum) {
    this->captainNum=CaptainNum;
}
void users::setTotalPeople(int totalPeople) {
    this->totalPeople=totalPeople;
}
void users::setUserStatus(int uNum, bool status) {
    this->userStatus[uNum-1]=status;
}
user* users::findCaptainPosition(user* head) {
    int cNum=this->captainNum;
    user* p=head->right;
    while (p->num!=cNum){
        p=p->right;
    }
    return p;
}
int users::getCaptainNum() {
    return this->captainNum;
}
int users::getNowPeople() {
    return this->nowPeople;
}
int users::getRedNum() const {
    return redNum;
}

void users::setRedNum(int redNum) {
    users::redNum = redNum;
}

int users::getBlackNum() const {
    return blackNum;
}

void users::setBlackNum(int blackNum) {
    users::blackNum = blackNum;
}
bool users::lookUpUserIdentity(int uNum) {
    return this->userIdentity[uNum-1];
}
int users::looUpRedEyeStatus(user *head) //返回睁眼红色人数
 {
   int sum= this->getNowPeople();
   user *p=head->right;
   int res=0;
   while (sum){
       int n=p->num;
       bool id=this->userIdentity[n-1];
       if(id&&p->eyeStatus)res++;
       p=p->right;
       sum--;
   }
   return res;
}
int users::lookUpBlackEyeStatus(user *head) {
    int sum= this->getNowPeople();
    user *p=head->right;
    int res=0;
    while (sum){
        int n=p->num;
        bool id=this->userIdentity[n-1];
        if(!id&&p->eyeStatus)res++;
        p=p->right;
        sum--;
    }
    return res;
}
bool users::checkUserStatus(int uNum) {
    return this->userStatus[uNum-1];
}
void users::setUserEyeStatus(user *head) {
    int sum= this->getNowPeople();
    user *p=head->right;
    while (sum){
        srand((int)time(NULL));
        bool eye=rand()%2;
        p->eyeStatus=eye;
        p=p->right;
        sum--;
    }
}
void users::setHaveDonePeople(int haveDonePeople){
    this->haveDonePeople=haveDonePeople;
};
int users:: getHaveDonePeople(){
    return  this->haveDonePeople;
};
void users:: setNowPosition(user* nowPosition){
    this->nowPostion=nowPostion;}
user* users::getNowPosition(){
    return this->nowPostion;
}
