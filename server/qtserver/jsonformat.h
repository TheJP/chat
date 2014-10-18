#ifndef JSONFORMAT_H
#define JSONFORMAT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>
#include "iformat.h"
#include "ikeyvaluereader.h"
#include "jsonreader.h"

class JsonFormat : public QObject, public IFormat
{
    Q_OBJECT
    Q_INTERFACES(IFormat)
public:
    explicit JsonFormat(QObject *parent = 0);
    QSharedPointer<IKeyValueReader> getReader(QByteArray input) override;
signals:

public slots:

};

#endif // JSONFORMAT_H
