#include "protocol.h"

#include "msgs/continuesession.h"
#include "msgs/empty.h"
#include "msgs/getconversations.h"
#include "msgs/login.h"
#include "msgs/logout.h"
#include "msgs/openconversation.h"
#include "msgs/sendmessage.h"
#include "streamable/response.h"
#include "streamable/responsesession.h"
#include "streamable/responseconversations.h"

Protocol::Protocol(QObject *parent) :
    QObject(parent)
{
}

QSharedPointer<IChatMsg> & Protocol::operator[](const int & index){
    return msgs[index];
}

void Protocol::initDefault(){
    set(RequestType::Login, QSharedPointer<IChatMsg>(new Login()));
    set(RequestType::Logout, QSharedPointer<IChatMsg>(new Logout()));
    set(RequestType::ContinueSession, QSharedPointer<IChatMsg>(new ContinueSession()));
    set(RequestType::GetConversations, QSharedPointer<IChatMsg>(new GetConversations()));
    set(RequestType::OpenConversation, QSharedPointer<IChatMsg>(new OpenConversation()));
    set(RequestType::SendMessage, QSharedPointer<IChatMsg>(new SendMessage()));
}

void Protocol::set(RequestType request, const QSharedPointer<IChatMsg> & msg){
    msgs[static_cast<int>(request)] = msg;
}

QSharedPointer<IChatMsg> Protocol::createRequest(RequestType request) const {
    if(!msgs.contains(static_cast<int>(request))) { return QSharedPointer<Empty>(new Empty()); }
    return msgs[static_cast<int>(request)]->create();
}

QSharedPointer<IChatMsg> Protocol::createResponse(RequestType request, bool success) const {
    return QSharedPointer<IChatMsg>(new Response(request, success));
}

QSharedPointer<IChatMsg> Protocol::createResponse(RequestType request, ErrorType error, const QString & errorText) const {
    return QSharedPointer<IChatMsg>(new Response(request, error, errorText));
}

QSharedPointer<IChatMsg> Protocol::createResponseSession(RequestType request, bool success, quint32 numSid, const QSharedPointer<QString> & sid, quint32 userId, const QSharedPointer<QString> & username) const {
    return QSharedPointer<IChatMsg>(new ResponseSession(numSid, sid, userId, username, request, success));
}

QSharedPointer<IChatMsg> Protocol::createResponseConversations(RequestType request, bool success, const ConversationsVector & conversations) const {
    return QSharedPointer<IChatMsg>(new ResponseConversations(conversations, request, success));
}
