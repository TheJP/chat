#include "login.h"

Login::Login(QObject *parent) :
    QObject(parent)
{
}

void Login::read(IKeyValueReader & stream){
    username = stream.readString(QStringLiteral("username"));
    password = stream.readString(QStringLiteral("password"));
}

void Login::write(IKeyValueWriter & stream){
    stream.writeString(QStringLiteral("username"), *username);
    stream.writeString(QStringLiteral("password"), *password);
}

QSharedPointer<IChatMsg> Login::create(){
    return QSharedPointer<Login>(new Login());
}

QSharedPointer<IChatMsg> Login::handle(const ServiceManager & manager){
    return manager.getUserService().login(*username, *password);
}
