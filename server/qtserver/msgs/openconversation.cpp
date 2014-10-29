#include "openconversation.h"

OpenConversation::OpenConversation(QObject *parent) :
    QObject(parent)
{
}

void OpenConversation::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void OpenConversation::write(IKeyValueWriter & stream){
    Q_UNUSED(stream);
}

QSharedPointer<IChatMsg> OpenConversation::create(){
    return QSharedPointer<OpenConversation>(new OpenConversation());
}

QSharedPointer<IChatMsg> OpenConversation::handle(const ServiceManager & manager){
    Q_UNUSED(manager);
    return QSharedPointer<OpenConversation>();
}
