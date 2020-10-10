#ifndef NUM_H
#define NUM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
class num : public QWidget
{
    Q_OBJECT
public:
    explicit num(QWidget *parent = nullptr);
    QLineEdit *edit;
public slots:
    void sendSlot();
signals:
void Mysignal(int num);
private:
  int n;

};


#endif // NUM_H
