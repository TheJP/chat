#include "userservice.h"
#include "servicemanager.h"
#include "../protocol.h"

//TODO: remove
#include <QDebug>
//TODO check permissions for different actions

UserService::UserService(ServiceManager * manager, const QString & applicationSalt, QObject *parent) :
    manager(manager), applicationSalt(applicationSalt), QObject(parent)
{
    //Prepare letters for session id calculation
    letters = new char[USERSERVICE_COUNT_LETTERS];
    int i;
    for(i = 0; i <= 9; ++i){ letters[i] = i+'0'; } //'0'-'9'
    for(i = 0; i < 26; ++i){ letters[i+10] = i+'a'; } //'a'-'z'
}

UserService::~UserService(){
    delete[] letters;
}

QSharedPointer<IChatMsg> UserService::login(const QString & username, const QString & password) const {
    qDebug() << "[UserService][login] username: " << username << " ";

    //** Check authentification **//
    quint32 userId = 0, numSid = 0;
    bool ok;
    QSqlQuery query;
    ok = query.prepare(
        "SELECT id, salt, password "
        "FROM user "
        "WHERE username = :username");
    query.bindValue(":username", username);
    ok = ok && query.exec();
    if(!ok){ qDebug() << query.lastError(); return manager->getProtocol().createResponse(RequestType::Login, ErrorType::Internal, QStringLiteral("")); }
    else if(!query.next()){
        qDebug() << "[wrong username]";
        ok = false; //Unkown username
    } else {
        userId = query.value(0).toUInt();
        QString dbSalt = query.value(1).toString();
        QString dbPassword = query.value(2).toString();
        QCryptographicHash sha256Password(QCryptographicHash::Sha256);
        sha256Password.addData(password.toUtf8());
        QCryptographicHash sha256(QCryptographicHash::Sha256);
        sha256.addData(applicationSalt.toUtf8() + sha256Password.result().toHex() + dbSalt.toUtf8());
        if(sha256.result().toHex() == dbPassword){
            qDebug() << "[correct]";
        }else{
            qDebug() << "[wrong password]";
            ok = false; //Wrong password
        }
    }

    //** Create Session **//
    QSharedPointer<QString> sid(new QString());
    if(!ok){ return manager->getProtocol().createResponse(RequestType::Login, ErrorType::Custom, QStringLiteral("Unkown username or password")); }
    else {
        for(int i = 0; i < USERSERVICE_SID_LENGTH; ++i){
            sid->append(letters[qrand()%USERSERVICE_COUNT_LETTERS]);
        }
        qDebug() << "session: " << *sid << endl;
        QSqlQuery querySession;
        ok = querySession.prepare(
            "INSERT INTO session (`sid`, `expire`, `user_id`) "
            "VALUES (:sid, DATE_ADD(NOW(), INTERVAL 1 YEAR), :user_id);");
        querySession.bindValue(":sid", *sid);
        querySession.bindValue(":user_id", userId);
        ok = ok && querySession.exec();
        if(ok){ numSid = querySession.lastInsertId().toInt(); }
    }
    if(!ok){ qDebug() << query.lastError(); return manager->getProtocol().createResponse(RequestType::Login, ErrorType::Internal, QStringLiteral("")); }
    else { return manager->getProtocol().createResponseSession(RequestType::Login, true, numSid, sid, QSharedPointer<QString>(new QString(username))); }
}

QSharedPointer<IChatMsg> UserService::logout(const QString & sid) const {
    //Undecided behaviour: What happens to clients with the same sessionid?
    Q_UNUSED(sid);
    return QSharedPointer<IChatMsg>();
}

QSharedPointer<IChatMsg> UserService::continueSession(const QString & sid) const {
    qDebug() << "[UserService][continueSession]";
    quint32 numSid;
    bool ok;
    QSqlQuery query;
    ok = query.prepare(
        "SELECT username, session.id "
        "FROM session LEFT JOIN user ON session.user_id = user.id "
        "WHERE sid = :sid");
    query.bindValue(":sid", sid);
    ok = ok && query.exec();
    if(!ok){ qDebug() << query.lastError(); return manager->getProtocol().createResponse(RequestType::ContinueSession, ErrorType::Internal, QStringLiteral("")); }
    else if(!query.next()){
        qDebug() << "[unkown sid]";
        //ok = false;
        return manager->getProtocol().createResponse(RequestType::ContinueSession, ErrorType::Custom, QStringLiteral("Unkown sid"));
    }else {
        QSharedPointer<QString> username(new QString(query.value(0).toString()));
        numSid = query.value(1).toInt();
        qDebug() << "[success] add client to session. username: " << *username;
        return manager->getProtocol().createResponseSession(RequestType::ContinueSession, true, numSid, QSharedPointer<QString>(new QString(sid)), username);
    }
}
