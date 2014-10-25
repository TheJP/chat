#ifndef IKEYVALUEREADER_H
#define IKEYVALUEREADER_H

#include <QString>
#include <QSharedPointer>
#include <QVector>

class IChatMsg;
//#include "ichatmsg.h"

class IKeyValueReader
{
    public:
        virtual ~IKeyValueReader() {}
        virtual int readInt(QString & key) = 0;
        virtual double readDouble(QString & key) = 0;
        virtual QSharedPointer<QString> readString(QString & key) = 0;
        virtual QVector<QSharedPointer<IChatMsg>> readArray(QString & key, IChatMsg & replicator) = 0;
};
Q_DECLARE_INTERFACE(IKeyValueReader, "JP.IKeyValueReader/1.0")

#endif // IKEYVALUEREADER_H
