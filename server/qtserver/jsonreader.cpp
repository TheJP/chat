#include "jsonreader.h"

JsonReader::JsonReader(QSharedPointer<QJsonObject> reader, QObject *parent) : QObject(parent) {}

int JsonReader::readInt(QString & key) const {
    return (*reader)[key].toInt();
}

double JsonReader::readDouble(QString & key) const {
    return (*reader)[key].toDouble();
}

QSharedPointer<QString> JsonReader::readString(QString & key) const {
    return (*reader)[key].toString();
}
