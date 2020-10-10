#include <iostream>
#include "users.h"
#include "voteBox.h"
#include <zconf.h>
using namespace std;
int totalNum;
float captainVoteNum;
int main() {
    cout<<"****************欢迎来到红黑夜法官游戏****************"<<endl<<"请输入游戏人数：";
    cin>>totalNum;
    if(totalNum==0)captainVoteNum=1.5;
    else captainVoteNum=0.5;
    cout<<"****************下面游戏开始****************"<<endl<<"下面开始竞选村长"<<endl;
    users* userChain=new users(totalNum,totalNum,0);
    user* head=userChain->createUserList(totalNum);
    for(int i=0;i<totalNum;i++){
        cout<<"现在是"<<i+1<<"号玩家的发言时间（按任意键结束发言并继续）"<<endl;
        getchar();
    }
    cout<<"****************发言结束，下面进行村长竞选****************"<<endl;
    voteBox *vBox= new voteBox(totalNum);
    for(int i=0;i<totalNum;i++){
        cout<<"现在是"<<i+1<<"号玩家的投票时间，请选择你的投票对象为："<<endl;
        int n;
        cin>>n;
        vBox->vote(n,0, false);
    }
    int maxNum=vBox->maxNumUserNum();
    while(maxNum!=1){
        int *maxNumUser=vBox->maxNUmUser();
        int a[maxNum];
        for(int i=0;i<maxNum;i++){
            a[i]=maxNumUser[i];
        }
        vBox->clearVoteBox();
        cout<<"有"<<maxNum<<"位玩家的票结果相同，下面进行第新一轮投票"<<endl;
        for(int i=0;i<totalNum;i++){
            cout<<"现在是"<<i+1<<"号玩家的投票时间，请选择你的投票对象为："<<endl;
            int n;
            cin>>n;
            bool flag= false;
            for(int i=0;i<maxNum;i++){
                if(n==a[i]){
                    flag= true;
                    break;}
            }
            if(!flag){
                cout<<"您的投票编号有误，请在";
                for(int m=0;m<maxNum;m++){
                    cout<<a[m]<<"、";
                }
                cout<<"中选择";
                i--;
                continue;
            }
            vBox->vote(n,0, false);
        }
        maxNum=vBox->maxNumUserNum();
    }
    int *captain=vBox->maxNUmUser();
    int captainNum=captain[0];
    userChain->setCaptainNum(captainNum);
    cout<<"****************"<<captainNum<<"号玩家当选警长****************"<<endl;
    int redNum,blackNum;
    redNum=userChain->looUpRedEyeStatus(head);
    blackNum=userChain->lookUpBlackEyeStatus(head);
    while (blackNum!=0&&redNum!=0) {
        cout << "下面请村长决定发言顺序，0代表左，1代表右"<<endl;
        int dir;
        cin >> dir;
        user *cap = userChain->findCaptainPosition(head);
        int sum=userChain->getNowPeople();
        if(dir){
            while (sum){
            cout<<"下面由"<<cap->right->num<<"号玩家发言"<<endl;
            getchar();
            cap=cap->right;
            sum--;}
        } else{
            while (sum){
                cap=cap->left;
                cout<<"下面由"<<cap->num<<"号玩家发言"<<endl;
                getchar();
                sum--;
        }
    }
        cout<<"****************发言结束，现在放逐进行投票****************"<<endl;
        vBox->clearVoteBox();
        sum=userChain->getNowPeople();
        user* p;
        p=head->right;
        vBox->clearVoteBox();
        while (sum){
            cout<<"现在是"<<p->num<<"号玩家的投票时间，请选择你的投票对象为："<<endl;
            int n;
            cin>>n;
            bool check=userChain->checkUserStatus(n);
            if(!check){
                cout<<"投票玩家已经出局";
                continue;
            }
            bool isCap;
            if(p->num==userChain->getCaptainNum())isCap = true;
            else isCap= false;
            sum--;
            p=p->right;
            vBox->vote(n,captainVoteNum, isCap);
        }
        maxNum=vBox->maxNumUserNum();
        while(maxNum!=1){
            int *maxNumUser=vBox->maxNUmUser();
            int a[maxNum];
            for(int i=0;i<maxNum;i++){
                a[i]=maxNumUser[i];
            }
            vBox->clearVoteBox();
            cout<<"有"<<maxNum<<"位玩家的票结果相同，下面进行第新一轮投票"<<endl;
            for(int i=0;i<totalNum;i++){
                cout<<"现在是"<<i+1<<"号玩家的投票时间，请选择你的投票对象为："<<endl;
                int n;
                cin>>n;
                bool flag= false;
                for(int i=0;i<maxNum;i++){
                    if(n==a[i]){
                        flag= true;
                        break;}
                }
                if(!flag){
                    cout<<"您的投票编号有误，请在";
                    for(int m=0;m<maxNum;m++){
                        cout<<a[m]<<"、";
                    }
                    cout<<"中选择";
                    i--;
                    continue;
                }
                bool isCap;
                if(i+1==userChain->getCaptainNum())isCap = true;
                else isCap= false;
                vBox->vote(n,captainNum,isCap);
            }
            maxNum=vBox->maxNumUserNum();
        }
        int * exile=vBox->maxNUmUser();
        int exilePersonNum=exile[0];
        if(userChain->checkUserStatus(exilePersonNum)){
        cout<<exilePersonNum<<"号玩家被放逐,他的身份是红"<<endl;} else{
            cout<<exilePersonNum<<"号玩家被放逐,他的身份是黑"<<endl;
        }
        userChain->deleteUser(exilePersonNum,head);
        captainNum=userChain->getCaptainNum();
        bool f=userChain->lookUpUserIdentity(exilePersonNum);

        if(exilePersonNum==captainNum){
            cout<<"请"<<exilePersonNum<<"号玩家移交警徽";
            bool c=false;
            while (!c){
            int newCapNum;
            cin>>newCapNum;
            c=userChain->checkUserStatus(newCapNum);
            if(!c){cout<<"该玩家已经被放逐或不存在，请重新输入";}
            else{
            userChain->setCaptainNum(newCapNum);
            c=true;}
            }
        }
        redNum=userChain->lookUpBlackEyeStatus(head);
        blackNum=userChain->looUpRedEyeStatus(head);
        if(redNum==0||blackNum==0)break;
        srand((int)time(NULL));
        bool night=rand()%2;
        if(night){
            cout<<"****************下面进入红夜****************"<<endl;
            userChain->setUserEyeStatus(head);
            int redEyeOpenNum=userChain->looUpRedEyeStatus(head);
            if(redEyeOpenNum%2==0)captainVoteNum=1;
            cout<<"村长票数为"<<captainVoteNum<<endl;
        } else {cout<<"****************下面进入黑夜****************"<<endl;
             userChain->setUserEyeStatus(head);
             int redEyeOpenNum=userChain->lookUpBlackEyeStatus(head);
             if(redEyeOpenNum%2==0)captainVoteNum=1;
            cout<<"村长票数为"<<captainVoteNum<<endl;
        }
    }
    if(redNum==0)cout<<"红方获胜";
    else cout<<"黑方获胜";
}
