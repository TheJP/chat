#ifndef ISTREAMABLE_H
#define ISTREAMABLE_H

#include <QSharedPointer>
#include "ikeyvaluereader.h"

class IKeyValueWriter;
//#include "ikeyvaluewriter.h"

class IStreamable
{
    public:
        virtual ~IStreamable() {}
        virtual void read(IKeyValueReader & stream) = 0;
        virtual void write(IKeyValueWriter & stream) = 0;
};
Q_DECLARE_INTERFACE(IStreamable, "JP.IStreamable/1.0")

#endif // ISTREAMABLE_H
