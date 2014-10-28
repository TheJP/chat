#ifndef IKEYVALUEWRITER_H
#define IKEYVALUEWRITER_H

#include <QString>
#include <QVector>
#include "istreamable.h"

class IKeyValueWriter
{
    public:
        virtual ~IKeyValueWriter() {}
        virtual void write(const QString & key, int value) = 0;
        virtual void write(const QString & key, double value) = 0;
        virtual void write(const QString & key, const QString & value) = 0;
        virtual void write(const QString & key, IStreamable & value) = 0;
        virtual void writeArray(const QString & key, const QVector<IStreamable*> & values) = 0;
};
Q_DECLARE_INTERFACE(IKeyValueWriter, "JP.IKeyValueWriter/1.0")

#endif // IKEYVALUEWRITER_H
