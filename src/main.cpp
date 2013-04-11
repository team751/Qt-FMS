#include "statuswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StatusWindow w;
    w.show();
    
    return a.exec();
}
