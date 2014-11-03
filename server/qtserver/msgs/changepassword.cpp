#include "changepassword.h"

ChangePassword::ChangePassword(QObject *parent) :
    QObject(parent)
{
}

void ChangePassword::read(IKeyValueReader & stream){
    oldPassword = stream.readString(QStringLiteral("oldpw"));
    newPassword = stream.readString(QStringLiteral("newpw"));
}

void ChangePassword::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("oldpw"), *oldPassword);
    stream.write(QStringLiteral("newpw"), *newPassword);
}

QSharedPointer<IChatMsg> ChangePassword::create(){
    return QSharedPointer<ChangePassword>(new ChangePassword());
}

QSharedPointer<IChatMsg> ChangePassword::handle(const ServiceManager & manager){
    return manager.getUserService().changePassword(getUserId(), *oldPassword, *newPassword);
}
