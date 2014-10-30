#include "register.h"

Register::Register(QObject *parent) :
    QObject(parent)
{
}

void Register::read(IKeyValueReader & stream){
    username = stream.readString(QStringLiteral("username"));
    email = stream.readString(QStringLiteral("email"));
    password = stream.readString(QStringLiteral("password"));
}

void Register::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("username"), *username);
    stream.write(QStringLiteral("email"), *email);
    stream.write(QStringLiteral("password"), *password);
}

QSharedPointer<IChatMsg> Register::create(){
    return QSharedPointer<Register>(new Register());
}

QSharedPointer<IChatMsg> Register::handle(const ServiceManager & manager){
    return manager.getUserService().createUser(*username, *email, *password);
}
