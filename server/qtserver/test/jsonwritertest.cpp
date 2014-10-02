#include "jsonwritertest.h"

JsonWriterTest::JsonWriterTest(QObject *parent) :
    QObject(parent)
{
}

void JsonWriterTest::init(){
    json = QSharedPointer<QJsonObject>(new QJsonObject());
    classUnderTest = new JsonWriter(json);
}

void JsonWriterTest::cleanup(){
    delete classUnderTest;
}

void JsonWriterTest::writeIntTest(){
    classUnderTest->writeInt(QStringLiteral("test01"), 5);
    QVERIFY((*json)["test01"].toInt() == 5);
}

void JsonWriterTest::writeDoubleTest(){
    classUnderTest->writeDouble(QStringLiteral("test02.01"), 5.6);
    classUnderTest->writeDouble(QStringLiteral("test02.02"), -1.337);
    QVERIFY((*json)["test02.01"].toDouble() == 5.6);
    QVERIFY((*json)["test02.02"].toDouble() == -1.337);
}

void JsonWriterTest::writeStringTest(){
    classUnderTest->writeString(QStringLiteral("test03"), QStringLiteral("hallo"));
    QVERIFY((*json)["test03"].toString() == QStringLiteral("hallo"));
}
