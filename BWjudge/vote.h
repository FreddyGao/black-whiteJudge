#ifndef VOTE_H
#define VOTE_H

#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
class vote : public QWidget
{
    Q_OBJECT
public:
    explicit vote(QWidget *parent = nullptr);

    QLineEdit *edit;
public slots:
    void sendSlot_2();
signals:
void Mysignal_2(int num);
private:
  int n;
};

#endif // VOTE_H
