#ifndef IKEYVALUEREADER_H
#define IKEYVALUEREADER_H

#include <QString>
#include <QSharedPointer>
#include <QVector>
//#include "istreamable.h"

class IKeyValueReader
{
    public:
        virtual ~IKeyValueReader() {}
        virtual int readInt(QString & key) = 0;
        virtual double readDouble(QString & key) = 0;
        //virtual QVector<> readArray(QString & key, T & (*toT)(IKeyValueReader)) = 0;
        virtual QSharedPointer<QString> readString(QString & key) = 0;
};
Q_DECLARE_INTERFACE(IKeyValueReader, "JP.IKeyValueReader/1.0")

#endif // IKEYVALUEREADER_H
