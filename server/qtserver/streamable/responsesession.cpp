#include "responsesession.h"

ResponseSession::ResponseSession(quint32 numSid, const QSharedPointer<QString> & sid, quint32 userId, const QSharedPointer<QString> & username, RequestType request, bool success, QObject *parent) :
    numSid(numSid), sid(sid), userId(userId), username(username), Response(request, success, parent)
{
}

void ResponseSession::read(IKeyValueReader & stream){
    Response::read(stream);
    sid = stream.readString(QStringLiteral("sid"));
    userId = stream.readInt(QStringLiteral("userid"));
    username = stream.readString(QStringLiteral("username"));
}

void ResponseSession::write(IKeyValueWriter & stream){
    Response::write(stream);
    stream.write(QStringLiteral("sid"), *sid);
    stream.write(QStringLiteral("userid"), static_cast<int>(userId));
    stream.write(QStringLiteral("username"), *username);
}

quint32 ResponseSession::getNumSid() const {
    return numSid;
}

quint32 ResponseSession::getUserId() const {
    return userId;
}
