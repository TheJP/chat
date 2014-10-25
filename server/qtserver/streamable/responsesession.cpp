#include "responsesession.h"

ResponseSession::ResponseSession(quint32 numSid, const QSharedPointer<QString> & sid, const QSharedPointer<QString> & username, RequestType request, bool success, QObject *parent) :
    numSid(numSid), sid(sid), username(username), Response(request, success, parent)
{
}

void ResponseSession::read(IKeyValueReader & stream){
    Response::read(stream);
    sid = stream.readString(QStringLiteral("sid"));
    username = stream.readString(QStringLiteral("username"));
}

void ResponseSession::write(IKeyValueWriter & stream){
    Response::write(stream);
    stream.write(QStringLiteral("sid"), *sid);
    stream.write(QStringLiteral("username"), *username);
}

quint32 ResponseSession::getNumSid() const {
    return numSid;
}
