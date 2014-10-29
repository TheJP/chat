#include "responsemessages.h"

ResponseMessages::ResponseMessages(const MessagesVector & messages, quint32 conversationId, RequestType request, bool success, QObject *parent) :
    messages(messages), conversationId(conversationId), Response(request, success, parent)
{
}

ResponseMessages::~ResponseMessages(){
    qDeleteAll(*messages);
}

void ResponseMessages::read(IKeyValueReader & stream){
    Response::read(stream);
    conversationId = stream.readInt(QStringLiteral("c"));
    //Read array
}

void ResponseMessages::write(IKeyValueWriter & stream){
    Response::write(stream);
    stream.write(QStringLiteral("c"), static_cast<int>(conversationId));
    stream.writeArray(QStringLiteral("msgs"), *messages);
}
