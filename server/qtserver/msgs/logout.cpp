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
    return QSharedPointer<IChatMsg>(new Logout());
}

QSharedPointer<IChatMsg> Logout::handle(ServiceManager manager){
    return QSharedPointer<IChatMsg>();
}
