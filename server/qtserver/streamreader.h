#ifndef STREAMREADER_H
#define STREAMREADER_H

#include <QDataStream>
#include <QObject>
#include <QSharedPointer>
#include "ikeyvaluereader.h"

class StreamReader : public QObject, public IKeyValueReader
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueReader)
private:
    QSharedPointer<QDataStream> reader;
public:
    explicit StreamReader(QSharedPointer<QDataStream> reader, QObject *parent = 0);
    template<class T>
    T read(QString & key) const;
    int readInt(QString & key) const;
    double readDouble(QString & key) const;
    QSharedPointer<QString> readString(QString & key) const;
signals:

public slots:

};

#endif // STREAMREADER_H
