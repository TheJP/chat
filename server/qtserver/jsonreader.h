#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonObject>
#include <QObject>
#include <QSharedPointer>
#include "ikeyvaluereader.h"

class JsonReader : public QObject, public IKeyValueReader
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueReader)
private:
    QSharedPointer<QJsonObject> reader;
public:
    explicit JsonReader(QSharedPointer<QJsonObject> reader, QObject *parent = 0);
    virtual int readInt(QString & key) const;
    virtual double readDouble(QString & key) const;
    virtual QSharedPointer<QString> readString(QString & key) const;
signals:

public slots:

};

#endif // JSONREADER_H
