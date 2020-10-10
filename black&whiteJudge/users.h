//
// Created by 高飞 on 2020/9/7.
//

#ifndef BLACK_WHITEJUDGE_USERS_H
#define BLACK_WHITEJUDGE_USERS_H

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
public:
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
};


#endif //BLACK_WHITEJUDGE_USERS_H
