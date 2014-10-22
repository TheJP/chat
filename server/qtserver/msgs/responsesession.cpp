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

quint32 ResponseSession::getNumSid() const {
    return numSid;
}
