#ifndef CHOOSE_H
#define CHOOSE_H
#include<QLineEdit>
#include <QWidget>
#include<QPushButton>
class choose : public QWidget
{
    Q_OBJECT
public:
    explicit choose(QWidget *parent = nullptr);

    QLineEdit *edit;
public slots:
    void sendSlot();
signals:
void Mysignal(int num);
private:
  int n;
};

#endif // CHOOSE_H
