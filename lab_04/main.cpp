#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSize sizes(800, 1080);

    w.resize(sizes);
    w.setMinimumSize(800, 600);

    w.show();
    return a.exec();
}
