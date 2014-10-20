#include "userservice.h"
#include "servicemanager.h"
#include "../protocol.h"

//TODO: remove
#include <QDebug>

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
    qDebug() << "[UserService] username: " << username << " ";

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
    if(!ok){ /* TODO: Internal error */ }
    else if(query.next()){
        userId = query.value(0).toUInt();
        QString dbSalt = query.value(1).toString();
        QString dbPassword = query.value(2).toString();
        QCryptographicHash sha256Password(QCryptographicHash::Sha256);
        sha256Password.addData(password.toUtf8());
        QCryptographicHash sha256(QCryptographicHash::Sha256);
        sha256.addData(applicationSalt.toUtf8() + sha256Password.result().toHex() + dbSalt.toUtf8());
        if(sha256.result().toHex() == dbPassword){
            qDebug() << "[correct]" << endl;
        }else{
            qDebug() << "[wrong]" << endl;
            ok = false;
        }
    }

    //** Create Session **//
    QSharedPointer<QString> sid(new QString());
    if(!ok){ /* TODO: Response fail */ }
    else {
        for(int i = 0; i < USERSERVICE_SID_LENGTH; ++i){
            sid->append(letters[qrand()%USERSERVICE_COUNT_LETTERS]);
        }
        qDebug() << "session: " << *sid << endl;
        QSqlQuery querySession;
        ok = querySession.prepare(
            "INSERT INTO session (`sid`, `expire`, `user_id`) "
            "VALUES (:sid, DATE_ADD(NOW(), INTERVAL 7 DAY), :user_id);");
        querySession.bindValue(":sid", *sid);
        querySession.bindValue(":user_id", userId);
        ok = ok && querySession.exec();
        numSid = querySession.lastInsertId().toInt();
    }
    if(!ok){ /* TODO: Internal error */ }
    else { return manager->getProtocol().createResponseSession(RequestType::Login, true, numSid, sid); }

    return QSharedPointer<IChatMsg>();
}
