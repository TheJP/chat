#include "sendmessage.h"

SendMessage::SendMessage(QObject *parent) :
    QObject(parent)
{
}

void SendMessage::read(IKeyValueReader & stream){
    conversationId = stream.readInt(QStringLiteral("c"));
    message = stream.readString(QStringLiteral("msg"));
}

void SendMessage::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("c"), static_cast<int>(conversationId));
    stream.write(QStringLiteral("msg"), *message);
}

QSharedPointer<IChatMsg> SendMessage::create(){
    return QSharedPointer<SendMessage>(new SendMessage());
}

QSharedPointer<IChatMsg> SendMessage::handle(const ServiceManager & manager){
    Q_UNUSED(manager);
    return QSharedPointer<SendMessage>();
}
