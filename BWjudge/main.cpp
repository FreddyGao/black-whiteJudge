#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
       MainWindow w;
       w.setFixedSize(800,800);
       w.setWindowTitle("Red&BlackNightJudge");

       w.show();

       return a.exec();
}
