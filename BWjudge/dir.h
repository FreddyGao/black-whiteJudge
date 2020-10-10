#ifndef DIR_H
#define DIR_H

#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
class dir : public QWidget
{
    Q_OBJECT
public:
    explicit dir(QWidget *parent = nullptr);
    QLineEdit *edit;
public slots:
    void sendSlot();
signals:
void Mysignal(int num);
private:
  int n;
};

#endif // DIR_H
