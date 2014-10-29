#ifndef RESPONSEMESSAGES_H
#define RESPONSEMESSAGES_H

#include <QObject>
#include <QHash>
#include <QSharedPointer>
#include <QVector>
#include "response.h"
#include "../protocol.h"
#include "../istreamable.h"
#include "../services/servicemanager.h"

class ResponseMessages final : public Response
{
    Q_OBJECT
private:
    //Optional: Can be set, if every messages belongs to the same conversation
    //It will always be deliverd: The default (=optional) value is 0
    quint32 conversationId;
    MessagesVector messages;
public:
    explicit ResponseMessages(const MessagesVector & messages, quint32 conversationId, RequestType request, bool success, QObject *parent = 0);
    ~ResponseMessages();
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
signals:

public slots:

};

#endif // RESPONSEMESSAGES_H
