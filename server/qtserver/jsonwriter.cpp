#include "jsonwriter.h"

JsonWriter::JsonWriter(QSharedPointer<QJsonObject> writer, QObject *parent) : writer(writer), QObject(parent) { }

void JsonWriter::write(QString & key, int value) {
    (*writer)[key] = value;
}

void JsonWriter::write(QString & key, double value) {
    (*writer)[key] = value;
}

void JsonWriter::write(QString & key, QString & value) {
    (*writer)[key] = value;
}

void JsonWriter::write(QString & key, IStreamable & value){
    QSharedPointer<QJsonObject> obj(new QJsonObject());
    JsonWriter subwriter(obj);
    value.write(subwriter);
    (*writer)[key] = *obj;
}

void JsonWriter::writeArray(QString & key, QVector<IStreamable *> & values){
    QJsonArray arr;
    for(IStreamable * value : values){
        QSharedPointer<QJsonObject> obj;
        JsonWriter subwriter(obj);
        value->write(subwriter);
        arr.append(*obj);
    }
    (*writer)[key] = arr;
}
