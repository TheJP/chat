#include "jsonwriter.h"

JsonWriter::JsonWriter(QSharedPointer<QJsonObject> writer, QObject *parent) : writer(writer), QObject(parent) { }

void writeInt(QString & key, int value) const {
    writer[key] = value;
}

void writeDouble(QString & key, double value) const {
    writer[key] = value;
}

void writeString(QString & key, QString & value) const {
    writer[key] = value;
}
