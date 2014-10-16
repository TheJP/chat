#include "streamreader.h"

StreamReader::StreamReader(QSharedPointer<QDataStream> reader, QObject *parent) : reader(reader), QObject(parent) { }

template<class T>
T StreamReader::read(QString & key) const {
    Q_UNUSED(key);
    T value; (*reader) >> value;
    return value;
}

int StreamReader::readInt(QString & key) const {
    return read<int>(key);
}

double StreamReader::readDouble(QString & key) const {
    return read<double>(key);
}

QSharedPointer<QString> StreamReader::readString(QString & key) const {
    Q_UNUSED(key);
    QSharedPointer<QString> value(new QString());
    (*reader) >> *value;
    return value;
}
