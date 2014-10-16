#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>

enum RquestType {
    //User Operations
    Login = 11,
    Logout = 12,
    Register = 13,
    ChangePassword = 14,
    ChangeProfile = 15,
    ContinueSession = 16, //Same as login, but sends sid to connect the client to the specified session

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
enum ResponseType {
    //1 client request to 1 server response
    Response = 1, //Sent with the Request Type (e.g. { type: Success, for: Login, Success: true/false, KEYS: VALUES })
    //1 client request to n server responses
    Notify = 2 //Sent with the Request Type
};

class protocol : public QObject
{
    Q_OBJECT
public:
    explicit protocol(QObject *parent = 0);

signals:

public slots:

};

#endif // PROTOCOL_H
