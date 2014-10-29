#ifndef ICHATMSG_H
#define ICHATMSG_H

#define KEY_MSG_TYPE QStringLiteral("t")

#include <QSharedPointer>
#include "ikeyvaluewriter.h"

class IKeyValueReader;
//#include "ikeyvaluereader.h"

class ServiceManager; //resolve cyclic include
//#include "services/servicemanager.h"

class IChatMsg
{
    private:
        quint32 userId = 0;
    public:
        virtual ~IChatMsg() {}
        virtual void read(IKeyValueReader & stream) = 0;
        virtual void write(IKeyValueWriter & stream) = 0;
        //Create new message of its own type
        //The Msg being targeted object and factory at the same time
        virtual QSharedPointer<IChatMsg> create() = 0;
        //Handles the message by calling the correct service methods
        //Returns an other message or a null message as a reply
        virtual QSharedPointer<IChatMsg> handle(const ServiceManager & manager) = 0;
        //User id
        void setUserId(quint32 userId){ this->userId = userId; }
        quint32 getUserId(){ return this->userId; }
};
Q_DECLARE_INTERFACE(IChatMsg, "JP.IChatMsg/1.0")

#endif // ICHATMSG_H
