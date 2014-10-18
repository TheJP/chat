#include "servicemanager.h"

ServiceManager::ServiceManager(const QSharedPointer<NotificationSender> & sender, QObject *parent) :
    sender(sender), QObject(parent)
{
}

const UserService & ServiceManager::getUserService() const {
    return user;
}

QSharedPointer<NotificationSender> ServiceManager::getNotificationSender() const {
    return sender;
}
