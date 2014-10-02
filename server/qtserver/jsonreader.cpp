#include "jsonreader.h"

JsonReader::JsonReader(QSharedPointer<QJsonObject> reader, QObject *parent) : reader(reader), QObject(parent) {}

int JsonReader::readInt(QString & key) {
    return (*this->reader)[key].toInt();
}

double JsonReader::readDouble(QString & key) {
    return (*this->reader)[key].toDouble();
}

QSharedPointer<QString> JsonReader::readString(QString & key) {
    QSharedPointer<QString> value(new QString((*this->reader)[key].toString()));
    return value;
}
