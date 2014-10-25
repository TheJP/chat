#include "responseconversations.h"

ResponseConversations::ResponseConversations(const QSharedPointer<QVector<Conversation*>> & conversations, RequestType request, bool success, QObject *parent) :
    conversations(conversations), Response(request, success, parent)
{
}

ResponseConversations::~ResponseConversations(){
    qDeleteAll(*conversations);
}

void ResponseConversations::read(IKeyValueReader & stream){
    Response::read(stream);
}

void ResponseConversations::write(IKeyValueWriter & stream){
    Response::write(stream);
}
