#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    srand(1000);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
