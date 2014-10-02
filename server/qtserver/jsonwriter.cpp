#include "jsonwriter.h"

JsonWriter::JsonWriter(QSharedPointer<QJsonObject> writer, QObject *parent) : writer(writer), QObject(parent) { }

void JsonWriter::writeInt(QString & key, int value) {
    (*writer)[key] = value;
}

void JsonWriter::writeDouble(QString & key, double value) {
    (*writer)[key] = value;
}

void JsonWriter::writeString(QString & key, QString & value) {
    (*writer)[key] = value;
}
