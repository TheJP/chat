#ifndef ICHATMSG_H
#define ICHATMSG_H

#include <QDataStream>
#include "IKeyValueReader.h"
#include "IKeyValueWriter.h"


class IChatMsg
{
    public:
        virtual ~IChatMsg() {}
        virtual void read(IKeyValueReader & stream) = 0;
        virtual void write(IKeyValueWriter & stream) = 0;
};
Q_DECLARE_INTERFACE(IChatMsg, "JP.IChatMsg/1.0")

#endif // ICHATMSG_H
