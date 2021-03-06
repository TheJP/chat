#ifndef MYFIRSTTEST_H
#define MYFIRSTTEST_H

#include <QObject>
#include <QtTest/QtTest>

class MyFirstTest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    { qDebug("called before everything else"); }
    void myFirstTest()
    { QVERIFY(1 == 1); }
    void mySecondTest()
    { QVERIFY(1 == 2); }
    void cleanupTestCase()
    { qDebug("called after myFirstTest and mySecondTest"); }
};

#endif // MYFIRSTTEST_H
