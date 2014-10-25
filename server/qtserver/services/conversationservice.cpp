#include "conversationservice.h"

#include "../protocol.h"

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
    int rows = ok ? query.size() : -1;
    if(!ok || rows < 0){ qDebug() << query.lastError(); return manager->getProtocol().createResponse(RequestType::GetConversations, ErrorType::Internal, QStringLiteral("")); }
    QSharedPointer<QVector<Conversation*>> conversations(new QVector<Conversation*>(rows));
    while(!query.next()){
        conversations->push_back(new Conversation());
        Conversation * con = conversations->last();
        con->id = query.value(0).toInt();
        con->title = query.value(1).toString();
        con->topic = query.value(2).toString();
        con->description = query.value(3).toString();
        con->root = query.value(4).toBool();
        con->parent_id = query.value(5).toInt();
    }
    return QSharedPointer<IChatMsg>();
}

QSharedPointer<IChatMsg> ConversationService::getOwnedConversations() const {
    //Later
    return QSharedPointer<IChatMsg>();
}
