#include "streamwriter.h"

StreamWriter::StreamWriter(QSharedPointer<QDataStream> writer, QObject *parent) : writer(writer), QObject(parent) { }

void StreamWriter::write(const QString & key, int value){
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::write(const QString & key, double value){
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::write(const QString & key, const QString & value){
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::write(const QString & key, IStreamable & value){
    Q_UNUSED(key);
    value.write(*this);
}

void StreamWriter::writeArray(const QString & key, const QVector<IStreamable *> & values){
    Q_UNUSED(key);
    (*writer) << values.size();
    for(IStreamable * value : values){
        value->write(*this);
    }
}
