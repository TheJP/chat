#ifndef JSONWRITERTEST_H
#define JSONWRITERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSharedPointer>
#include <QJsonObject>
#include "../jsonwriter.h"

class JsonWriterTest : public QObject
{
    Q_OBJECT
private:
    JsonWriter * classUnderTest;
    QSharedPointer<QJsonObject> json;
public:
    explicit JsonWriterTest(QObject *parent = 0);
private slots:
    void init();
    void cleanup();
    void writeIntTest();
    void writeDoubleTest();
    void writeStringTest();

};

#endif // JSONWRITERTEST_H
