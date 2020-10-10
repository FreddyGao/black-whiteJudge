#ifndef VOTE_2_H
#define VOTE_2_H

#include <QWidget>
#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
class vote_2 : public QWidget
{
    Q_OBJECT
public:
    explicit vote_2(QWidget *parent = nullptr);

    QLineEdit *edit;
public slots:
    void sendSlot_2();
signals:
void Mysignal_2(int num);
private:
  int n;

public slots:
};

#endif // VOTE_2_H
