#ifndef RESPONSECONVERSATIONS_H
#define RESPONSECONVERSATIONS_H

#include <QObject>
#include <QHash>
#include <QSharedPointer>
#include <QVector>
#include "response.h"
#include "../protocol.h"
#include "../istreamable.h"
#include "../services/servicemanager.h"

class ResponseConversations final : public Response
{
    Q_OBJECT
private:
    ConversationsVector conversations;
public:
    explicit ResponseConversations(const ConversationsVector & conversations, RequestType request, bool success, QObject *parent = 0);
    ~ResponseConversations();
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
signals:

public slots:

};

#endif // RESPONSECONVERSATIONS_H
