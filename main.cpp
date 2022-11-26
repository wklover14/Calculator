#include "maincalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainCalculator w;

    w.show();
    return a.exec();
}
