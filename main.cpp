#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    StylesSheets::load();
    StylesSheets::setCurrentStyle("Blue");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
