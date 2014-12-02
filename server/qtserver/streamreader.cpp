#include "streamreader.h"

StreamReader::StreamReader(QSharedPointer<QDataStream> reader, QObject *parent) : reader(reader), QObject(parent) { }

template<class T>
T StreamReader::read(const QString & key) const {
    Q_UNUSED(key);
    T value; (*reader) >> value;
    return value;
}

int StreamReader::readInt(const QString & key){
    return read<int>(key);
}

double StreamReader::readDouble(const QString & key){
    return read<double>(key);
}

QSharedPointer<QString> StreamReader::readString(const QString & key){
    Q_UNUSED(key);
    QSharedPointer<QString> value(new QString());
    (*reader) >> *value;
    return value;
}

QVector<QSharedPointer<IChatMsg>> StreamReader::readArray(const QString &key, IChatMsg &replicator){
    Q_UNUSED(key);
    Q_UNUSED(replicator);
    return QVector<QSharedPointer<IChatMsg>>();
}
