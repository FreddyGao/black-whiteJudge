#include "voteBox.h"
#include <iostream>
using  namespace std;
 voteBox::voteBox(int n) {
    this->vBox=new float [n];
    for(int i=0;i<n;i++){
        vBox[i]=0;
    }
    this->vBoxSize=n;
}
int voteBox::maxNumUserNum() {
    float max=0;
    for(int i=0;i<this->vBoxSize;i++){
        if(this->vBox[i]>max)max=this->vBox[i];
    }
    int num=0;
    for(int i=0;i<this->vBoxSize;i++){
        if(this->vBox[i]==max)num++;
    }
    return num;
}
int* voteBox::maxNUmUser() {
    float max=0;
    for(int i=0;i<this->vBoxSize;i++){
        if(this->vBox[i]>max)max=this->vBox[i];
    }
    float *copy = new float [this->vBoxSize];//莫名其妙的改变了
    for(int i=0;i<this->vBoxSize;i++){
        copy[i]=this->vBox[i];
    }
    int num=0;
    for(int i=0;i<this->vBoxSize;i++){
        if(copy[i]==max)num++;
    }
    int maxMember[num];
    int j=0;
    for(int i=0;i<this->vBoxSize;i++){
        if(copy[i]==max){
            maxMember[j]=i+1;
            j++;}
    }
    return maxMember;
}
void voteBox::vote(int user, float captainVoteNum, bool isCap) {
    if(isCap){
        this->vBox[user-1]+=captainVoteNum;
    }
    this->vBox[user-1]++;
}
void voteBox::clearVoteBox() {
    for(int i=0;i<this->vBoxSize;i++){
        vBox[i]=0;
    }
}
