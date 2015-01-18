#include "logout.h"

Logout::Logout(QObject *parent) :
    QObject(parent)
{
}

void Logout::read(IKeyValueReader & stream){
    sid = stream.readString(QStringLiteral("sid"));
}

void Logout::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("sid"), *sid);
}

QSharedPointer<IChatMsg> Logout::create(){
    return QSharedPointer<Logout>(new Logout());
}

QSharedPointer<IChatMsg> Logout::handle(const ServiceManager & manager){
    return manager.getUserService().logout(*sid);
}
