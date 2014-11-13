#include "user.h"
#include "../ikeyvaluewriter.h"

User::User(QObject *parent) :
    QObject(parent)
{
}

void User::read(IKeyValueReader & stream){
    id = stream.readInt(QStringLiteral("id"));
    username = stream.readString(QStringLiteral("username"));
    status = stream.readString(QStringLiteral("status"));
    description = stream.readString(QStringLiteral("description"));
}

void User::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("id"), static_cast<int>(id));
    stream.write(QStringLiteral("username"), *username);
    stream.write(QStringLiteral("status"), *status);
    stream.write(QStringLiteral("description"), *description);
}
