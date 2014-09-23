#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QJsonObject>
#include <QObject>
#include "ikeyvaluewriter.h"

class JsonWriter : public QObject, public IKeyValueWriter
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueWriter)
private:
    QSharedPointer<QJsonObject> writer;
public:
    explicit JsonWriter(QSharedPointer<QJsonObject> writer, QObject *parent = 0);
    virtual void writeInt(QString & key, int value) const;
    virtual void writeDouble(QString & key, double value) const;
    virtual void writeString(QString & key, QString & value) const;
signals:

public slots:

};

#endif // JSONWRITER_H
