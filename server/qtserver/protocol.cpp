#include "protocol.h"

#include "msgs/login.h"

protocol::protocol(QObject *parent) :
    QObject(parent)
{
}

QSharedPointer<IChatMsg> & protocol::operator[](const int & index){
    return msgs[index];
}

void protocol::initDefault(){
    msgs[RquestType::Login] = QSharedPointer<IChatMsg>(new Login());
}
