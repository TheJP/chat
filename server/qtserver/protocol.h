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

    //Chat Operations
    SendMessage = 31,
    OpenConversation = 32,  //Gets latest messages and registers session to conversation -> Called when opening conversation
    CloseConversation = 33, //Unregister session from conversation
    GetMessagesOlder = 34,  //Messages before a given timestamp -> Called to get older messages then the given

    //Admin Operations
    Mute = 51, //Temp (with timestamp) or Perma as parameter
    Ban = 53,  //Temp (with timestamp) or Perma as parameter

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
