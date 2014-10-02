#include <QCoreApplication>

#ifdef QT_DEBUG
    #include "test/testmain.h"
#endif

int main(int argc, char *argv[])
{
#ifdef QT_DEBUG
    TestMain tests;
    tests.execute();
#endif

    QCoreApplication a(argc, argv);

    return a.exec();
}
