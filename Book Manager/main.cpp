#include "BookManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookManager w;
    w.show();
    return a.exec();
}
