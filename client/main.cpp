#include "messenger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Messenger w;
    return a.exec();
}
