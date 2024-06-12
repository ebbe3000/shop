#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/imgs/icon.png"));

    QFile f(":qdarkstyle/dark/darkstyle.qss");

    if (!f.exists())
        qDebug() << "Unable to set stylesheet, file not found\n";
    else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

    MainWindow w;
    w.show();

    return a.exec();
}

// deleting photos for adding product in productadd form :)

// edit personal data
