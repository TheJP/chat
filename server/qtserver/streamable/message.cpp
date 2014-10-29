#include "message.h"
#include "../ikeyvaluewriter.h"

Message::Message(QObject *parent) :
    QObject(parent)
{
}

void Message::read(IKeyValueReader & stream){
    id = stream.readInt(QStringLiteral("id"));
    message = stream.readString(QStringLiteral("msg"));
    time = stream.readInt(QStringLiteral("time"));
    conversationId = stream.readInt(QStringLiteral("c"));
    userId = stream.readInt(QStringLiteral("userid"));
    username = stream.readString(QStringLiteral("username"));
}

void Message::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("id"), static_cast<int>(id));
    stream.write(QStringLiteral("msg"), *message);
    stream.write(QStringLiteral("time"), time);
    stream.write(QStringLiteral("c"), static_cast<int>(conversationId));
    stream.write(QStringLiteral("userid"), static_cast<int>(userId));
    stream.write(QStringLiteral("username"), *username);
}
