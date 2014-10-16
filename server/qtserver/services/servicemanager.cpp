#include "servicemanager.h"

ServiceManager::ServiceManager(QObject *parent) :
    QObject(parent)
{
}

const UserService & ServiceManager::getUserService() const {
    return user;
}
