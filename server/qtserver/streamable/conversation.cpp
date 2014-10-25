#include "conversation.h"
#include "../ikeyvaluewriter.h"

Conversation::Conversation(QObject *parent) :
    QObject(parent)
{
}

void Conversation::read(IKeyValueReader & stream){
    id = stream.readInt(QStringLiteral("id"));
    title = *stream.readString(QStringLiteral("title"));
    topic = *stream.readString(QStringLiteral("topic"));
    description = *stream.readString(QStringLiteral("description"));
    root = stream.readInt(QStringLiteral("root")) == 1;
    parent_id = stream.readInt(QStringLiteral("parent_id"));
}

void Conversation::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("id"), static_cast<int>(id));
    stream.write(QStringLiteral("title"), title);
    stream.write(QStringLiteral("topic"), topic);
    stream.write(QStringLiteral("description"), description);
    stream.write(QStringLiteral("root"), root ? 1 : 0);
    stream.write(QStringLiteral("parent_id"), static_cast<int>(parent_id));
}
