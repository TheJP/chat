#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QJsonObject>
#include <QJsonArray>
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
    void write(QString & key, int value) override;
    void write(QString & key, double value) override;
    void write(QString & key, QString & value) override;
    void write(QString & key, IStreamable & value) override;
    void writeArray(QString & key, QVector<IStreamable*> & values) override;
signals:

public slots:

};

#endif // JSONWRITER_H
