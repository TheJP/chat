#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include "userservice.h"
#include "../notificationsender.h"

class ServiceManager : public QObject
{
    Q_OBJECT
private:
    QSharedPointer<NotificationSender> sender;
    //Services
    UserService user;
public:
    explicit ServiceManager(const QSharedPointer<NotificationSender> & sender, QObject *parent = 0);
    const UserService & getUserService() const;
    QSharedPointer<NotificationSender> getNotificationSender() const;
signals:

public slots:

};

#endif // SERVICEMANAGER_H
