#include "responseconversations.h"

ResponseConversations::ResponseConversations(QSharedPointer<QVector<Conversation>> conversations, RequestType request, bool success, QObject *parent) :
    conversations(conversations), Response(request, success, parent)
{
}

void ResponseConversations::read(IKeyValueReader & stream){
    Response::read(stream);
    for(Conversation conversation : *conversations){

    }
}

void ResponseConversations::write(IKeyValueWriter & stream){
    Response::write(stream);
}
