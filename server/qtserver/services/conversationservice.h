#ifndef CONVERSATIONSERVICE_H
#define CONVERSATIONSERVICE_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include "servicemanager.h"
#include "../ichatmsg.h"
#include "conversation.h"

class ConversationService : public QObject
{
    Q_OBJECT
private:
    ServiceManager * manager;
public:
    explicit ConversationService(ServiceManager * manager, QObject *parent = 0);
    QSharedPointer<IChatMsg> getPublicConversations() const;
    QSharedPointer<IChatMsg> getOwnedConversations() const; //Later
signals:

public slots:

};

#endif // CONVERSATIONSERVICE_H
