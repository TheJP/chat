#include "protocol.h"

#include "msgs/login.h"
#include "msgs/logout.h"

Protocol::Protocol(QObject *parent) :
    QObject(parent)
{
}

QSharedPointer<IChatMsg> & Protocol::operator[](const int & index){
    return msgs[index];
}

void Protocol::initDefault(){
    set(RequestType::Login, QSharedPointer<Login>(new Login()));
    set(RequestType::Logout, QSharedPointer<Logout>(new Logout()));
}

void Protocol::set(RequestType request, const QSharedPointer<IChatMsg> & msg){
    msgs[static_cast<int>(request)] = msg;
}

QSharedPointer<IChatMsg> Protocol::createRequest(RequestType request) const {
    return msgs[static_cast<int>(request)]->create();
}
