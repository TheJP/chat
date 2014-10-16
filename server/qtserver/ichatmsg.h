#ifndef ICHATMSG_H
#define ICHATMSG_H

#include <QSharedPointer>
#include "IKeyValueReader.h"
#include "IKeyValueWriter.h"

class IChatMsg
{
    public:
        virtual ~IChatMsg() {}
        virtual void read(IKeyValueReader & stream) = 0;
        virtual void write(IKeyValueWriter & stream) = 0;
        //Create new message of its own type
        //The Msg being targeted object and factory at the same time
        virtual QSharedPointer<IChatMsg> create() = 0;
        //Handles the message by calling the correct service methods
        //Returns an other message or a null message as a reply
        virtual QSharedPointer<IChatMsg> handle(/*ServiceManager manager, NotificationSender sender*/) = 0;
};
Q_DECLARE_INTERFACE(IChatMsg, "JP.IChatMsg/1.0")

#endif // ICHATMSG_H
