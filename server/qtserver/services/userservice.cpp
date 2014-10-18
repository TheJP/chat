#include "userservice.h"

//TODO: remove
#include <QDebug>

UserService::UserService(const QString & applicationSalt, QObject *parent) :
    applicationSalt(applicationSalt), QObject(parent)
{
    //Prepare letters for session id calculation
    letters = new char[36];
    int i;
    for(i = 0; i <= 9; ++i){ letters[i] = i+'0'; }
    for(i = 0; i < 26; ++i){ letters[i+10] = i+'a'; }
}

UserService::~UserService(){
    delete[] letters;
}

QSharedPointer<IChatMsg> UserService::login(const QString & username, const QString & password) const {
    qDebug() << "[UserService] username: " << username << " ";

    //** Check authentification **//
    bool ok;
    QSqlQuery query;
    ok = query.prepare(
        "SELECT salt, password "
        "FROM user "
        "WHERE username = :username");
    query.bindValue(":username", username);
    ok = ok && query.exec();
    if(!ok){ /* TODO: Internal error */ }
    else if(query.next()){
        QString dbSalt = query.value(0).toString();
        QString dbPassword = query.value(1).toString();
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
    if(!ok){ /* TODO: Response fail */ }
    else {
        QByteArray sid;
        for(int i = 0; i < 256; ++i){
            sid.append(letters[qrand()%36]);
        }
        qDebug() << "session: " << sid << endl;
    }

    return QSharedPointer<IChatMsg>();
}
