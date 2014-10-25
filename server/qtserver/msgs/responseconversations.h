#ifndef RESPONSECONVERSATIONS_H
#define RESPONSECONVERSATIONS_H

#include <QObject>
#include <QHash>
#include <QSharedPointer>
#include <QVector>
#include "conversation.h"
#include "response.h"
#include "../protocol.h"
#include "../services/servicemanager.h"

class ResponseConversations final : public Response
{
    Q_OBJECT
private:
    QSharedPointer<QVector<Conversation>> conversations;
public:
    explicit ResponseConversations(QSharedPointer<QVector<Conversation>> conversations, RequestType request, bool success, QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
signals:

public slots:

};

#endif // RESPONSECONVERSATIONS_H
