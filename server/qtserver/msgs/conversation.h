#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>
#include <QSharedPointer>
#include "../ikeyvaluereader.h"
#include "../ikeyvaluewriter.h"

typedef struct {
    void write(IKeyValueWriter & stream){
    }
    void read(IKeyValueReader & stream){
    }

} Conversation;

#endif // CONVERSATION_H
