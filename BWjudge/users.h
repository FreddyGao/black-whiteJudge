#ifndef USERS_H
#define USERS_H


//
// Created by 高飞 on 2020/9/7.
//

#ifndef BLACK_WHITEJUDGE_USERS_H
#define BLACK_WHITEJUDGE_USERS_H
#include <votebox.h>
#include<vote.h>
#include<dir.h>
#include<vote_2.h>
#include<choose.h>
struct user{
    int num;
    bool eyeStatus;
    user *left;
    user *right;
};
class users {
private:
    int totalPeople; //总共人数
    int nowPeople; //当前人数
    int captainNum;//村长编号
    int* userStatus;//用户状态
    int redNum;
    int blackNum;
    bool* userIdentity;
    int haveDonePeople;
    user* nowPostion;
    voteBox* vBox;
    bool dirct;
    bool day;
    bool night;

public:
    bool getNight();
    void setNight(bool night);
    user* findPeoplePosition(int num,user*head);
    void setDir(bool dir);
    bool getDir();
    user* createUserList(int totalPeople);
    user* deleteUser(int num,user* head);
    users(int totalNum, int nowPeople,int capitalNum);
    void setTotalPeople(int totalPeople);
    void setNowPeople(int nowPeople);
    void setCaptainNum(int CaptainNum);
    void setUserStatus(int user, bool status);
    bool checkUserStatus(int uNum);
    user* findCaptainPosition(user* head);
    int getNowPeople();
    int getCaptainNum();
    int getRedNum() const;
    void setRedNum(int redNum);
    int getBlackNum() const;
    void setBlackNum(int blackNum);
    bool lookUpUserIdentity(int uNum);
    int looUpRedEyeStatus(user* head);
    int lookUpBlackEyeStatus(user* head);
    void setUserEyeStatus(user *head);
    void setHaveDonePeople(int haveDonePeople);
    void setNowPosition(user* nowPosition);
    int getHaveDonePeople();
    int getTotalPeople();
    bool getDay();
    void setDay(bool day);
    user* getNowPosition();
    void setVoteBox(voteBox* voteBox);
    voteBox* getVoteBox();
    class dir d;
    vote_2 v2;
    choose c;
    int sts;
    int t1;
    int t2;
    bool voteSts;
};


#endif //BLACK_WHITEJUDGE_USERS_H


#endif // USERS_H
