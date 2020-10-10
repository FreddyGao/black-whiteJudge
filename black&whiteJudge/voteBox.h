//
// Created by 高飞 on 2020/9/7.
//

#ifndef BLACK_WHITEJUDGE_VOTEBOX_H
#define BLACK_WHITEJUDGE_VOTEBOX_H


class voteBox {
private:
    float * vBox;
     int vBoxSize;
public:
    void vote(int user, float captainVoteNum, bool isCap);
    int maxNumUserNum();
    int* maxNUmUser();
    voteBox(int n);
    void clearVoteBox();
};


#endif //BLACK_WHITEJUDGE_VOTEBOX_H
