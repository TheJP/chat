#include "login.h"

Login::Login(QObject *parent) :
    QObject(parent)
{
}

void Login::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void Login::write(IKeyValueWriter & stream){
    Q_UNUSED(stream);
}

QSharedPointer<IChatMsg> Login::create(){
    return QSharedPointer<IChatMsg>(new Login());
}

QSharedPointer<IChatMsg> Login::handle(ServiceManager manager){
    return QSharedPointer<IChatMsg>();
}
