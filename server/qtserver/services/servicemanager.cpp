#include "servicemanager.h"

ServiceManager::ServiceManager(const QSharedPointer<NotificationSender> & sender, const QString & applicationSalt, QObject *parent) :
    sender(sender), user(applicationSalt), QObject(parent)
{
}

const UserService & ServiceManager::getUserService() const {
    return user;
}

QSharedPointer<NotificationSender> ServiceManager::getNotificationSender() const {
    return sender;
}
