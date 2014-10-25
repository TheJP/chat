#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>
#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include "ikeyvaluereader.h"
#include "ichatmsg.h"

class JsonReader : public QObject, public IKeyValueReader
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueReader)
private:
    QSharedPointer<QJsonObject> reader;
public:
    explicit JsonReader(QSharedPointer<QJsonObject> reader, QObject *parent = 0);
    int readInt(QString & key) override;
    double readDouble(QString & key) override;
    QSharedPointer<QString> readString(QString & key) override;
    QVector<QSharedPointer<IChatMsg>> readArray(QString & key, IChatMsg & replicator) override;
signals:

public slots:

};

#endif // JSONREADER_H
