#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>

typedef struct {
    quint32 id;
    QString title;
    QString topic;
    QString description;
    bool root;
    quint32 parent_id;
} Conversation;

#endif // CONVERSATION_H
