#include "testmain.h"

TestMain::TestMain(QObject *parent) :
    QObject(parent)
{
}

void TestMain::execute(){
    QTest::qExec(new JsonReaderTest());
    QTest::qExec(new JsonWriterTest());
}
