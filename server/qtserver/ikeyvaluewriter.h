#ifndef IKEYVALUEWRITER_H
#define IKEYVALUEWRITER_H

#include <QString>
#include <QVector>
#include "istreamable.h"

class IKeyValueWriter
{
    public:
        virtual ~IKeyValueWriter() {}
        virtual void write(QString & key, int value) = 0;
        virtual void write(QString & key, double value) = 0;
        virtual void write(QString & key, QString & value) = 0;
        virtual void write(QString & key, IStreamable & value) = 0;
        virtual void writeArray(QString & key, QVector<IStreamable*> & values) = 0;
};
Q_DECLARE_INTERFACE(IKeyValueWriter, "JP.IKeyValueWriter/1.0")

#endif // IKEYVALUEWRITER_H
