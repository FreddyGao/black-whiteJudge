#ifndef VOTEBOX_H
#define VOTEBOX_H


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


#endif // VOTEBOX_H
