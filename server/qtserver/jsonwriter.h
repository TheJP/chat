#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QJsonObject>
#include <QObject>
#include <QSharedPointer>
#include "ikeyvaluewriter.h"

class JsonWriter : public QObject, public IKeyValueWriter
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueWriter)
private:
    QSharedPointer<QJsonObject> writer;
public:
    explicit JsonWriter(QSharedPointer<QJsonObject> writer, QObject *parent = 0);
    void writeInt(QString & key, int value) override;
    void writeDouble(QString & key, double value) override;
    void writeString(QString & key, QString & value) override   ;
signals:

public slots:

};

#endif // JSONWRITER_H
