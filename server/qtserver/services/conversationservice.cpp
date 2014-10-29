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
    bool ok;
    QSqlQuery query;
    ok = query.prepare(
        "SELECT id, title, topic, description, root, parent_id "
        "FROM conversation "
        "WHERE root = 1 OR parent_id IS NOT NULL");
    ok = ok && query.exec();
    //* Potential performance improvement: */ int rows = ok ? (manager->getSupportSize() ? query.size() : 0) : -1; //Initial vector size
    int rows = 0;
    if(!ok || rows < 0){ qDebug() << "[fail] " << query.lastError(); return manager->getProtocol().createResponse(RequestType::GetConversations, ErrorType::Internal, QStringLiteral("")); }
    ConversationsVector conversations(new QVector<IStreamable*>(rows));
    while(query.next()){
        conversations->push_back(new Conversation());
        Conversation * con = static_cast<Conversation*>(conversations->last());
        con->id = query.value(0).toInt();
        con->title = query.value(1).toString();
        con->topic = query.value(2).toString();
        con->description = query.value(3).toString();
        con->root = query.value(4).toBool();
        con->parent_id = query.value(5).toInt();
    }
    return manager->getProtocol().createResponseConversations(RequestType::GetConversations, true, conversations);
}

QSharedPointer<IChatMsg> ConversationService::getOwnedConversations() const {
    //Later
    return QSharedPointer<IChatMsg>();
}

QSharedPointer<IChatMsg> ConversationService::openConversation(quint32 conversationId, quint32 userId) const {
    Q_UNUSED(userId);
    qDebug() << "[ConversationService][openConversation] c: " << conversationId << " u: " << userId;
    //Get newest MAX_MESSAGES_ON_OPEN messages
    bool ok;
    QSqlQuery query;
    ok = query.prepare(
        "SELECT m.id, m.message, m.time, m.conversation_id, u.id, u.username "
        "FROM message AS m JOIN user AS u ON m.user_id = u.id "
        "WHERE m.conversation_id = :conversationid "
        "ORDER BY m.time DESC "
        "LIMIT 0, :max");
    query.bindValue(":conversationid", conversationId);
    query.bindValue(":max", MAX_MESSAGES_ON_OPEN);
    ok = ok && query.exec();
    if(!ok){ qDebug() << query.lastError(); return manager->getProtocol().createResponse(RequestType::OpenConversation, ErrorType::Internal, QStringLiteral("")); }
    MessagesVector messages(new QVector<IStreamable*>()); //Potential performance improvement: predefine row count
    while(query.next()){
        messages->push_back(new Message());
        Message * msg = static_cast<Message*>(messages->last());
        msg->id = query.value(0).toInt();
        msg->message = QSharedPointer<QString>(new QString(query.value(1).toString()));
        msg->time = query.value(2).toDateTime().toTime_t();
        msg->conversationId = query.value(3).toInt();
        msg->userId = query.value(4).toInt();
        msg->username = QSharedPointer<QString>(new QString(query.value(5).toString()));
    }
    return manager->getProtocol().createResponseMessages(RequestType::OpenConversation, true, messages, conversationId);
}
