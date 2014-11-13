#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
//Map with fast lookup
#include <QHash>
#include <QSharedPointer>
#include "ichatmsg.h"
#include "msgs/login.h"

typedef QSharedPointer<QVector<IStreamable*>> StreamableVector;

enum class RequestType {
    //User Operations
    Login = 11,
    Logout = 12,
    Register = 13,
    ChangePassword = 14,
    ChangeProfile = 15,
    ContinueSession = 16, //Same as login, but sends sid to connect the client to the specified session
    GetUser = 17, //Gets the profile information for a pecified user (identified with his id)

    //Chat Operations
    SendMessage = 31,
    OpenConversation = 32,   //Gets latest messages and registers session to conversation -> Called when opening conversation
    CloseConversation = 33,  //Unregister session from conversation
    GetMessagesOlder = 34,   //Messages before a given timestamp -> Called to get older messages then the given
    CreateConversation = 35,
    DeleteConversation = 36,
    ChangeConversation = 37,
    InviteConversation = 38,
    ChangeConversationPermission = 39,
    GetConversations = 40,   //Public or joined private Conversations as argument

    //Admin Operations
    Mute = 51, //Temp (with timestamp) or Perma as parameter
    Ban = 52,  //Temp (with timestamp) or Perma as parameter
    ChangePermission = 53

};
enum class ResponseType {
    //1 client request to 1 server response
    Response = 1, //Sent with the Request Type (e.g. { type: Success, for: Login, Success: true/false, KEYS: VALUES })
    //1 client request to n server responses
    Notify = 2 //Sent with the Request Type
};
enum class ErrorType {
    None = 0,
    Forbidden = 403, //Access denied
    NotFound = 404,
    ImATeapot = 418,
    Internal = 500,
    Custom = 600
};

class Protocol : public QObject
{
    Q_OBJECT
private:
    QHash<int, QSharedPointer<IChatMsg>> msgs;
public:
    explicit Protocol(QObject *parent = 0);
    QSharedPointer<IChatMsg> & operator[](const int & index);
    void initDefault();
    void set(RequestType request, const QSharedPointer<IChatMsg> & msg);
    QSharedPointer<IChatMsg> createRequest(RequestType request) const;
    QSharedPointer<IChatMsg> createResponse(RequestType request, bool success) const;
    QSharedPointer<IChatMsg> createResponse(RequestType request, ErrorType error, const QString & errorText) const;
    QSharedPointer<IChatMsg> createResponseSession(RequestType request, bool success, quint32 numSid, const QSharedPointer<QString> & sid, quint32 userId, const QSharedPointer<QString> & username) const;
    QSharedPointer<IChatMsg> createResponseStreamables(RequestType request, bool success, const QSharedPointer<QString> & type, const StreamableVector & streamables) const;
    QSharedPointer<IChatMsg> createResponseMessages(RequestType request, bool success, const StreamableVector & messages, quint32 conversationId) const;
signals:

public slots:

};

#endif // PROTOCOL_H
