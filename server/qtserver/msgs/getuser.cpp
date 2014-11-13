#include "getuser.h"

GetUser::GetUser(QObject *parent) :
    QObject(parent)
{
}

void GetUser::read(IKeyValueReader & stream){
    userId = stream.readInt(QStringLiteral("userid"));
}

void GetUser::write(IKeyValueWriter & stream){
    stream.write(QStringLiteral("userid"), static_cast<int>(userId));
}

QSharedPointer<IChatMsg> GetUser::create(){
    return QSharedPointer<GetUser>(new GetUser());
}

QSharedPointer<IChatMsg> GetUser::handle(const ServiceManager & manager){
    return manager.getUserService().getUserProfile(this->userId);
}
