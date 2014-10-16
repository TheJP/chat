#include "streamwriter.h"

StreamWriter::StreamWriter(QSharedPointer<QDataStream> writer, QObject *parent) : writer(writer), QObject(parent) { }

void StreamWriter::writeInt(QString & key, int value) const {
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::writeDouble(QString & key, double value) const {
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::writeString(QString & key, QString & value) const {
    Q_UNUSED(key);
    (*writer) << value;
}
