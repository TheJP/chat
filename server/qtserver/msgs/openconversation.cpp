#include "openconversation.h"

OpenConversation::OpenConversation(QObject *parent) :
    QObject(parent)
{
}

void OpenConversation::read(IKeyValueReader & stream){
    conversationId = stream.readInt(QStringLiteral("c"));
}

void OpenConversation::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("c"), static_cast<int>(conversationId));
}

QSharedPointer<IChatMsg> OpenConversation::create(){
    return QSharedPointer<OpenConversation>(new OpenConversation());
}

QSharedPointer<IChatMsg> OpenConversation::handle(const ServiceManager & manager){
    return manager.getConversationService().openConversation(conversationId, getUserId());
}
