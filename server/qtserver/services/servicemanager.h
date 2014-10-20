#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include "userservice.h"
#include "../notificationsender.h"

class Protocol; //resolve cyclic reference
//#include "../protocol.h"

class ServiceManager : public QObject
{
    Q_OBJECT
private:
    QSharedPointer<NotificationSender> sender;
    QSharedPointer<Protocol> protocol;
    //Services
    UserService user;
public:
    explicit ServiceManager(const QSharedPointer<NotificationSender> & sender, const QSharedPointer<Protocol> & protocol, const QString & applicationSalt, QObject *parent = 0);
    const UserService & getUserService() const;
    const NotificationSender & getNotificationSender() const;
    const Protocol & getProtocol() const;
signals:

public slots:

};

#endif // SERVICEMANAGER_H
