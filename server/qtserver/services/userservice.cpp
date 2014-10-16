#include "userservice.h"

#include <QDebug>

UserService::UserService(QObject *parent) :
    QObject(parent)
{
}

QSharedPointer<IChatMsg> UserService::login(const QString & username, const QString & password) const {
    qDebug() << "username: " << username << " password: " << password << endl;
    return QSharedPointer<IChatMsg>();
}
