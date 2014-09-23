#ifndef IKEYVALUEWRITER_H
#define IKEYVALUEWRITER_H

#include <QString>

class IKeyValueWriter
{
    public:
        virtual ~IKeyValueWriter() {}
        virtual void writeInt(QString & key, int value) = 0;
        virtual void writeDouble(QString & key, double value) = 0;
        virtual void writeString(QString & key, QString & value) = 0;
};
Q_DECLARE_INTERFACE(IKeyValueWriter, "JP.IKeyValueWriter/1.0")

#endif // IKEYVALUEWRITER_H
