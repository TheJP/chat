#include "getconversations.h"

GetConversations::GetConversations(QObject *parent) :
    QObject(parent)
{
}

void GetConversations::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void GetConversations::write(IKeyValueWriter & stream){
    Q_UNUSED(stream);
}

QSharedPointer<IChatMsg> GetConversations::create(){
    return QSharedPointer<GetConversations>(new GetConversations());
}

QSharedPointer<IChatMsg> GetConversations::handle(const ServiceManager & manager){
    Q_UNUSED(manager);
    return QSharedPointer<GetConversations>();
}
