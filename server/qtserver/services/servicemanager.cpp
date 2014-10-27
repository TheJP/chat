#include "servicemanager.h"

ServiceManager::ServiceManager(const QSharedPointer<NotificationSender> & sender, const QSharedPointer<Protocol> & protocol, const QString & applicationSalt, QObject *parent) :
    sender(sender), protocol(protocol), user(this, applicationSalt), conversation(this), QObject(parent)
{
    supportSize = QSqlDatabase::database().driver()->hasFeature(QSqlDriver::QuerySize);
}

const UserService & ServiceManager::getUserService() const {
    return user;
}

const ConversationService & ServiceManager::getConversationService() const {
    return conversation;
}

const NotificationSender & ServiceManager::getNotificationSender() const {
    return *sender;
}

const Protocol & ServiceManager::getProtocol() const {
    return *protocol;
}

bool ServiceManager::getSupportSize() const {
    return supportSize;
}
