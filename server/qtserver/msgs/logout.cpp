#include "logout.h"

Logout::Logout(QObject *parent) :
    QObject(parent)
{
}

void Logout::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void Logout::write(IKeyValueWriter & stream){
    Q_UNUSED(stream);
}

QSharedPointer<IChatMsg> Logout::create(){
    return QSharedPointer<Logout>(new Logout());
}

QSharedPointer<IChatMsg> Logout::handle(const ServiceManager & manager){
    //TODO: implement
    Q_UNUSED(manager);
    return QSharedPointer<Logout>();
}
