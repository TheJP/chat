#include "jsonreadertest.h"

JsonReaderTest::JsonReaderTest(QObject *parent) :
    QObject(parent)
{
}

void JsonReaderTest::init(){
    QSharedPointer<QJsonObject> json(new QJsonObject());
    (*json)["test01"] = 5;
    (*json)["test02.01"] = 5.6;
    (*json)["test02.02"] = -1.337;
    (*json)["test03"] = QStringLiteral("hallo");
    this->classUnderTest = new JsonReader(json);
}

void JsonReaderTest::cleanup(){
    delete this->classUnderTest;
}

void JsonReaderTest::readIntTest(){
    QVERIFY(this->classUnderTest->readInt(QStringLiteral("test01")) == 5);
}

void JsonReaderTest::readDoubleTest(){
    QVERIFY(this->classUnderTest->readDouble(QStringLiteral("test02.01")) == 5.6);
    QVERIFY(this->classUnderTest->readDouble(QStringLiteral("test02.02")) == -1.337);
}

void JsonReaderTest::readStringTest(){
    QVERIFY(QStringLiteral("hallo") == *this->classUnderTest->readString(QStringLiteral("test03")));
}
