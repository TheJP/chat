#ifndef JSONREADERTEST_H
#define JSONREADERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSharedPointer>
#include <QJsonObject>
#include "../jsonreader.h"

class JsonReaderTest : public QObject
{
    Q_OBJECT
private:
    JsonReader * classUnderTest;
public:
    explicit JsonReaderTest(QObject *parent = 0);
private slots:
    void init();
    void cleanup();
    void readIntTest();
    void readDoubleTest();
    void readStringTest();
};

#endif // JSONREADERTEST_H
