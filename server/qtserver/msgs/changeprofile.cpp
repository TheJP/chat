#include "changeprofile.h"

ChangeProfile::ChangeProfile(QObject *parent) :
    QObject(parent)
{
}

void ChangeProfile::read(IKeyValueReader & stream){
    status = stream.readString(QStringLiteral("status"));
    description = stream.readString(QStringLiteral("description"));
}

void ChangeProfile::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("status"), *status);
    stream.write(QStringLiteral("description"), *description);
}

QSharedPointer<IChatMsg> ChangeProfile::create(){
    return QSharedPointer<ChangeProfile>(new ChangeProfile());
}

QSharedPointer<IChatMsg> ChangeProfile::handle(const ServiceManager & manager){
    return manager.getUserService().changeProfile(this->getUserId(), *status, *description);
}
