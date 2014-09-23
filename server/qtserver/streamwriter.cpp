#include "streamwriter.h"

StreamWriter::StreamWriter(QSharedPointer<QDataStream> writer, QObject *parent) : writer(writer), QObject(parent) { }

void StreamWriter::writeInt(QString & key, int value) const {
    (*writer) << value;
}

void StreamWriter::writeDouble(QString & key, double value) const {
    (*writer) << value;
}

void StreamWriter::writeString(QString & key, QString & value) const {
    (*writer) << value;
}
