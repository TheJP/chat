#include "jsonformat.h"

JsonFormat::JsonFormat(QObject *parent) :
    QObject(parent)
{
}

QSharedPointer<IKeyValueReader> JsonFormat::getReader(QByteArray input) {
    QJsonDocument datain(QJsonDocument::fromJson(input));
    QSharedPointer<QJsonObject> json(new QJsonObject(datain.object()));
    QSharedPointer<IKeyValueReader> result(new JsonReader(json));
    return result;
}

