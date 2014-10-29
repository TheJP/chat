#ifndef CONVERSATIONSERVICE_H
#define CONVERSATIONSERVICE_H

#define MAX_MESSAGES_ON_OPEN 15
#define MAX_MESSAGES_ON_GET_OLD 30

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QDateTime>
#include "../ichatmsg.h"
#include "../istreamable.h"

class ConversationService : public QObject
{
    Q_OBJECT
private:
    ServiceManager * manager;
public:
    explicit ConversationService(ServiceManager * manager, QObject *parent = 0);
    QSharedPointer<IChatMsg> getPublicConversations() const;
    QSharedPointer<IChatMsg> getOwnedConversations() const; //Later
    QSharedPointer<IChatMsg> openConversation(quint32 conversationId, quint32 userId) const;
signals:

public slots:

};

#endif // CONVERSATIONSERVICE_H
