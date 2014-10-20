#include "responsesession.h"

ResponseSession::ResponseSession(quint32 numSid, const QSharedPointer<QString> & sid, RequestType request, bool success, QObject *parent) :
    numSid(numSid), sid(sid), Response(request, success, parent)
{
}

void ResponseSession::read(IKeyValueReader & stream){
    Response::read(stream);
    sid = stream.readString(QStringLiteral("sid"));
}

void ResponseSession::write(IKeyValueWriter & stream){
    Response::write(stream);
    stream.writeString(QStringLiteral("sid"), *sid);
}

//Invalid for this specific type
QSharedPointer<IChatMsg> ResponseSession::create(){
    return QSharedPointer<ResponseSession>();
}

//Invalid for this specific type
QSharedPointer<IChatMsg> ResponseSession::handle(const ServiceManager & manager){
    Q_UNUSED(manager);
    return QSharedPointer<ResponseSession>();
}
