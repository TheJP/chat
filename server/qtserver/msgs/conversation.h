#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>
#include <QSharedPointer>
#include "../ikeyvaluereader.h"
#include "../ikeyvaluewriter.h"

typedef struct {
    quint32 id;
    QString title;
    QString topic;
    QString description;
    bool root;
    quint32 parent_id;
    void write(IKeyValueWriter & stream){
        stream.writeInt(QStringLiteral("id"), id);
        stream.writeString(QStringLiteral("title"), title);
        stream.writeString(QStringLiteral("topic"), topic);
        stream.writeString(QStringLiteral("description"), description);
        stream.writeInt(QStringLiteral("root"), root ? 1 : 0);
        stream.writeInt(QStringLiteral("parent_id"), parent_id);
    }
    void read(IKeyValueReader & stream){
        id = stream.readInt(QStringLiteral("id"));
        title = *stream.readString(QStringLiteral("title"));
        topic = *stream.readString(QStringLiteral("topic"));
        description = *stream.readString(QStringLiteral("description"));
        root = stream.readInt(QStringLiteral("root")) == 1;
        parent_id = stream.readInt(QStringLiteral("parent_id"));
    }

} Conversation;

#endif // CONVERSATION_H
