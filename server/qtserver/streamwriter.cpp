#include "streamwriter.h"

StreamWriter::StreamWriter(QSharedPointer<QDataStream> writer, QObject *parent) : writer(writer), QObject(parent) { }

void StreamWriter::write(QString & key, int value){
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::write(QString & key, double value){
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::write(QString & key, QString & value){
    Q_UNUSED(key);
    (*writer) << value;
}

void StreamWriter::write(QString & key, IStreamable & value){
    Q_UNUSED(key);
    value.write(*this);
}

void StreamWriter::writeArray(QString & key, QVector<IStreamable *> & values){
    Q_UNUSED(key);
    (*writer) << values.size();
    for(IStreamable * value : values){
        value->write(*this);
    }
}
