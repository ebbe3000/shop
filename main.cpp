#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // zrobic odczyt i zapis obrazka
    // add product categories

    return a.exec();
}


// deleting photos for adding product
