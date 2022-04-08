#include "cihm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CIhm w;
    w.showFullScreen();
    return a.exec();
}
