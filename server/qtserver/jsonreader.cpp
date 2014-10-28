#include "jsonreader.h"

JsonReader::JsonReader(QSharedPointer<QJsonObject> reader, QObject *parent) : reader(reader), QObject(parent) {}

int JsonReader::readInt(const QString & key){
    return (*this->reader)[key].toInt();
}

double JsonReader::readDouble(const QString & key){
    return (*this->reader)[key].toDouble();
}

QSharedPointer<QString> JsonReader::readString(const QString & key){
    QSharedPointer<QString> value(new QString((*this->reader)[key].toString()));
    return value;
}

QVector<QSharedPointer<IChatMsg>> JsonReader::readArray(const QString & key, IChatMsg & replicator){
    QJsonArray arr (std::move((*this->reader)[key].toArray()));
    QVector<QSharedPointer<IChatMsg>> result(arr.size());
    for(QJsonValueRef value : arr){
        QSharedPointer<QJsonObject> obj(new QJsonObject(value.toObject()));
        JsonReader subreader(obj);
        result.push_back(replicator.create());
        result.last()->read(subreader);
    }
    return std::move(result);
}
