#include "servicemanager.h"

ServiceManager::ServiceManager(const QSharedPointer<NotificationSender> & sender, const QSharedPointer<Protocol> & protocol, const QString & applicationSalt, QObject *parent) :
    sender(sender), protocol(protocol), user(this, applicationSalt), QObject(parent)
{
}

const UserService & ServiceManager::getUserService() const {
    return user;
}

const NotificationSender & ServiceManager::getNotificationSender() const {
    return *sender;
}

const Protocol & ServiceManager::getProtocol() const {
    return *protocol;
}
