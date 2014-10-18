#ifndef IFORMAT_H
#define IFORMAT_H

#include <QObject>
#include <QSharedPointer>
#include "ikeyvaluereader.h"

class IFormat
{
public:
    virtual ~IFormat() {}
    virtual QSharedPointer<IKeyValueReader> getReader(QByteArray input) = 0;
};
Q_DECLARE_INTERFACE(IFormat, "JP.IFormat/1.0")

#endif // IFORMAT_H
