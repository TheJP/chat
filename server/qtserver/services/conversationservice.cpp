#include "conversationservice.h"

#include "servicemanager.h"
#include "../protocol.h"
#include "../streamable/conversation.h"
#include "../streamable/message.h"

//TODO: remove
#include <QDebug>

ConversationService::ConversationService(ServiceManager * manager, QObject *parent) :
    manager(manager), QObject(parent)
{
}

QSharedPointer<IChatMsg> ConversationService::getPublicConversations() const {
    qDebug() << "[ConversationService][getPublicConversations]";
    //Get public conversations
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare(
        "SELECT id, title, topic, description, root, parent_id "
        "FROM conversation "
        "WHERE root = 1 OR parent_id IS NOT NULL;");
    bool ok = false;
    if(!query.isNull()){ ok = manager->getDbService().exec(query); }
    //* Potential performance improvement: */ int rows = ok ? (manager->getSupportSize() ? query->size() : 0) : -1; //Initial vector size
    int rows = 0;
    if(!ok || rows < 0){ return manager->getProtocol().createResponse(RequestType::GetConversations, ErrorType::Internal, QStringLiteral("")); }
    StreamableVector conversations(new QVector<IStreamable*>(rows));
    while(query->next()){
        conversations->push_back(new Conversation());
        Conversation * con = static_cast<Conversation*>(conversations->last());
        con->id = query->value(0).toInt();
        con->title = query->value(1).toString();
        con->topic = query->value(2).toString();
        con->description = query->value(3).toString();
        con->root = query->value(4).toBool();
        con->parent_id = query->value(5).toInt();
    }
    return manager->getProtocol().createResponseStreamables(RequestType::GetConversations, true, QSharedPointer<QString>(new QString("conversations")), conversations);
}

QSharedPointer<IChatMsg> ConversationService::getOwnedConversations() const {
    //Later
    return QSharedPointer<IChatMsg>();
}

QSharedPointer<IChatMsg> ConversationService::openConversation(quint32 conversationId, quint32 userId) const {
    qDebug() << "[ConversationService][openConversation] c: " << conversationId << " u: " << userId;
    //Get newest MAX_MESSAGES_ON_OPEN messages
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare(
        "SELECT m.id, m.message, m.time, m.conversation_id, u.id, u.username "
        "FROM message AS m JOIN user AS u ON m.user_id = u.id "
        "WHERE m.conversation_id = :conversationid "
        "ORDER BY m.time DESC "
        "LIMIT 0, :max;");
    bool ok = false;
    if(!query.isNull()){
        query->bindValue(":conversationid", conversationId);
        query->bindValue(":max", MAX_MESSAGES_ON_OPEN);
        ok = manager->getDbService().exec(query);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::OpenConversation, ErrorType::Internal, QStringLiteral("")); }
    StreamableVector messages(new QVector<IStreamable*>()); //Potential performance improvement: predefine row count
    while(query->next()){
        messages->push_back(new Message());
        Message * msg = static_cast<Message*>(messages->last());
        msg->id = query->value(0).toInt();
        msg->message = QSharedPointer<QString>(new QString(query->value(1).toString()));
        msg->time = query->value(2).toDateTime().toTime_t();
        msg->conversationId = query->value(3).toInt();
        msg->userId = query->value(4).toInt();
        msg->username = QSharedPointer<QString>(new QString(query->value(5).toString()));
    }
    return manager->getProtocol().createResponseMessages(RequestType::OpenConversation, true, messages, conversationId);
}

QSharedPointer<IChatMsg> ConversationService::sendMessage(quint32 conversationId, quint32 userId, const QSharedPointer<QString> & message) const {
    qDebug() << "[ConversationService][sendMessage] c: " << conversationId << " u: " << userId << " message: " << *message;

    //Filter invalid user
    if(userId <= 0){ return manager->getProtocol().createResponse(RequestType::SendMessage, ErrorType::Custom, QStringLiteral("You have to login, before sending messages")); }

    //Create new message
    StreamableVector messages(new QVector<IStreamable*>());
    messages->push_back(new Message());
    Message * msg = static_cast<Message*>(messages->last());
    msg->message = message;
    msg->time = QDateTime::currentDateTime().toTime_t();
    msg->conversationId = conversationId;
    msg->userId = userId;

    //Filter invalid messages
    int messageLength = msg->message->length();
    if(messageLength < 1 || messageLength > 500){ return manager->getProtocol().createResponse(RequestType::SendMessage, ErrorType::Custom, QStringLiteral("Invalid message size")); }

    //Insert new message
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare(
        "INSERT INTO message (`message`, `time`, `conversation_id`, `user_id`) "
        "VALUES (:message, :time, :conversationid, :userid);");
    bool ok = false;
    if(!query.isNull()){
        query->bindValue(":message", *msg->message);
        query->bindValue(":time", msg->time);
        query->bindValue(":conversationid", msg->conversationId);
        query->bindValue(":userid", msg->userId);
        ok = manager->getDbService().exec(query);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::SendMessage, ErrorType::Internal, QStringLiteral("")); }
    msg->id = query->lastInsertId().toInt();

    //Get username for this message
    QSharedPointer<QSqlQuery> userQuery = manager->getDbService().prepare("SELECT username FROM user WHERE user.id = :userid");
    ok = false;
    if(!userQuery.isNull()){
        userQuery->bindValue(":userid", userId);
        ok = manager->getDbService().exec(userQuery);
    }
    if(!ok || !userQuery->next()){ return manager->getProtocol().createResponse(RequestType::SendMessage, ErrorType::Internal, QStringLiteral("")); }
    msg->username = QSharedPointer<QString>(new QString(userQuery->value(0).toString()));

    //Send notifications to users
    QSharedPointer<IChatMsg> response = manager->getProtocol().createResponseMessages(RequestType::SendMessage, true, messages, conversationId);
    emit manager->getNotificationSender().newNotification(*response, QList<int>());

    return QSharedPointer<IChatMsg>(); //No direct response; Sending user gets notification as well
}
