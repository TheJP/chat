#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <QDataStream>
#include <QObject>
#include <QSharedPointer>
#include "ikeyvaluewriter.h"

class StreamWriter : public QObject, public IKeyValueWriter
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueWriter)
private:
    QSharedPointer<QDataStream> writer;
public:
    explicit StreamWriter(QSharedPointer<QDataStream> writer, QObject *parent = 0);
    virtual void writeInt(QString & key, int value) const;
    virtual void writeDouble(QString & key, double value) const;
    virtual void writeString(QString & key, QString & value) const;
signals:

public slots:

};

#endif // STREAMWRITER_H
