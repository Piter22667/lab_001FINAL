#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; // вікно, яке ми бачимо
    w.show();
    return a.exec();
}
