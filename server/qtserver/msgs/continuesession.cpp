#include "continuesession.h"

ContinueSession::ContinueSession(QObject *parent) :
    QObject(parent)
{
}

void ContinueSession::read(IKeyValueReader & stream){
    sid = stream.readString(QStringLiteral("sid"));
}

void ContinueSession::write(IKeyValueWriter & stream){
    stream.writeString(QStringLiteral("sid"), *sid);
}

QSharedPointer<IChatMsg> ContinueSession::create(){
    return QSharedPointer<ContinueSession>(new ContinueSession());
}

QSharedPointer<IChatMsg> ContinueSession::handle(const ServiceManager & manager){
    return manager.getUserService().continueSession(*sid);
}
