#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlDriver>
#include "userservice.h"
#include "conversationservice.h"
#include "dbservice.h"
#include "../notificationsender.h"

class Protocol; //resolve cyclic reference
//#include "../protocol.h"

class ServiceManager : public QObject
{
    Q_OBJECT
private:
    QSharedPointer<NotificationSender> sender;
    QSharedPointer<Protocol> protocol;
    bool supportSize;
    //Services
    UserService user;
    ConversationService conversation;
    DbService db;
public:
    explicit ServiceManager(const QSharedPointer<NotificationSender> & sender, const QSharedPointer<Protocol> & protocol, const QString & applicationSalt, QObject *parent = 0);
    const UserService & getUserService() const;
    const ConversationService & getConversationService() const;
    const DbService & getDbService() const;
    const NotificationSender & getNotificationSender() const;
    const Protocol & getProtocol() const;
    bool getSupportSize() const;
signals:

public slots:

};

#endif // SERVICEMANAGER_H
