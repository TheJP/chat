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

QSharedPointer<QString> UserService::generateString(int length) const {
    char str[USERSERVICE_MAX_GENERATE_LENGTH+1];
    int i;
    for(i = 0; i < length; ++i){
        str[i] = letters[qrand()%USERSERVICE_COUNT_LETTERS];
    }
    str[i] = '\0';
    return QSharedPointer<QString>(new QString(str));
}

//Encrypt password
QSharedPointer<QString> UserService::generatePassword(const QString & password, const QString & salt) const {
    QCryptographicHash sha256Password(QCryptographicHash::Sha256);
    sha256Password.addData(password.toUtf8());
    QCryptographicHash sha256(QCryptographicHash::Sha256);
    sha256.addData(applicationSalt.toUtf8() + sha256Password.result().toHex() + salt.toUtf8());
    return QSharedPointer<QString>(new QString(sha256.result().toHex()));
}

QSharedPointer<IChatMsg> UserService::login(const QString & username, const QString & password) const {
    qDebug() << "[UserService][login] username: " << username << " ";

    //** Check authentification **//
    quint32 userId = 0, numSid = 0;
    QString dbUsername;
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare(
        "SELECT id, username, salt, password "
        "FROM user "
        "WHERE username = :username OR email = :email");
    bool ok = false;
    if(!query.isNull()){
        query->bindValue(":username", username);
        query->bindValue(":email", username);
        ok = manager->getDbService().exec(query);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::Login, ErrorType::Internal, QStringLiteral("")); }
    else if(!query->next()){
        qDebug() << "[wrong username]";
        ok = false; //Unkown username
    } else {
        userId = query->value(0).toUInt();
        dbUsername = query->value(1).toString();
        QString dbSalt = query->value(2).toString();
        QString dbPassword = query->value(3).toString();
        QSharedPointer<QString> sha256 = generatePassword(password.toUtf8(), dbSalt.toUtf8());
        if(*sha256 == dbPassword){
            qDebug() << "[correct]";
        }else{
            qDebug() << "[wrong password]";
            ok = false; //Wrong password
        }
    }

    //** Create Session **//
    QSharedPointer<QString> sid(new QString());
    if(!ok){ return manager->getProtocol().createResponse(RequestType::Login, ErrorType::Custom, QStringLiteral("Wrong username or password")); }
    else {
        sid = this->generateString(USERSERVICE_SID_LENGTH);
        qDebug() << "session: " << *sid << endl;
        QSharedPointer<QSqlQuery> querySession = manager->getDbService().prepare(
            "INSERT INTO session (`sid`, `expire`, `user_id`) "
            "VALUES (:sid, DATE_ADD(NOW(), INTERVAL 1 YEAR), :user_id);");
        ok = false;
        if(!querySession.isNull()){
            querySession->bindValue(":sid", *sid);
            querySession->bindValue(":user_id", userId);
            ok = manager->getDbService().exec(querySession);
        }
        if(!ok){ return manager->getProtocol().createResponse(RequestType::Login, ErrorType::Internal, QStringLiteral("")); }
        else {
            numSid = querySession->lastInsertId().toInt();
            return manager->getProtocol().createResponseSession(
                RequestType::Login, true, numSid, sid, userId, QSharedPointer<QString>(new QString(dbUsername)));
        }
    }
}

QSharedPointer<IChatMsg> UserService::logout(const QString & sid) const {
    //Undecided behaviour: What happens to clients with the same sessionid?
    Q_UNUSED(sid);
    return QSharedPointer<IChatMsg>();
}

QSharedPointer<IChatMsg> UserService::continueSession(const QString & sid) const {
    qDebug() << "[UserService][continueSession]";
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare(
        "SELECT user.id, username, session.id "
        "FROM session LEFT JOIN user ON session.user_id = user.id "
        "WHERE sid = :sid");
    bool ok = false;
    if(!query.isNull()){
        query->bindValue(":sid", sid);
        ok = manager->getDbService().exec(query);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::ContinueSession, ErrorType::Internal, QStringLiteral("")); }
    else if(!query->next()){
        qDebug() << "[unkown sid]";
        //ok = false;
        return manager->getProtocol().createResponse(RequestType::ContinueSession, ErrorType::Custom, QStringLiteral("Unkown sid"));
    }else {
        quint32 userId = query->value(0).toInt();
        QSharedPointer<QString> username(new QString(query->value(1).toString()));
        quint32 numSid = query->value(2).toInt();
        qDebug() << "[success] add client to session. username: " << *username;
        return manager->getProtocol().createResponseSession(RequestType::ContinueSession, true, numSid, QSharedPointer<QString>(new QString(sid)), userId, username);
    }
}

QSharedPointer<IChatMsg> UserService::createUser(const QString & username, const QString & email, const QString & password) const {
    qDebug() << "[UserService][register] username: " << username << " email: " << email;

    //Validate inputs
    int usernameLength = username.length();
    if(usernameLength < 2 || usernameLength > 24 || email.length() < 3 || password.length() < 6){
        //Should already be handled by client -> Probably someone testing out the system, who doesn't need an error message
        return manager->getProtocol().createResponse(RequestType::SendMessage, ErrorType::Custom, QStringLiteral("Invalid input"));
    }

    //Check for duplicates
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare(
        "SELECT username, email "
        "FROM user "
        "WHERE username = :username OR email = :email");
    bool ok = false;
    if(!query.isNull()){
        query->bindValue(":username", username);
        query->bindValue(":email", email);
        ok = manager->getDbService().exec(query);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::Register, ErrorType::Internal, QStringLiteral("")); }
    else if(query->next()){
        qDebug() << "Duplicate username or email";
        return manager->getProtocol().createResponse(RequestType::Register, ErrorType::Custom,
            QString::compare(username, query->value(0).toString(), Qt::CaseInsensitive) == 0 ?
            QStringLiteral("Username is already used") : QStringLiteral("Mail is already used")
        );
    }

    //Encrypt password
    QSharedPointer<QString> salt = this->generateString(USERSERVICE_SALT_LENGTH);
    QSharedPointer<QString> sha256 = generatePassword(password.toUtf8(), *salt);

    //Create user
    QSharedPointer<QSqlQuery> queryCreate = manager->getDbService().prepare(
        "INSERT INTO user (`username`, `email`, `salt`, `password`) "
        "VALUES (:username, :email, :salt, :password);");
    ok = false;
    if(!queryCreate.isNull()){
        queryCreate->bindValue(":username", username);
        queryCreate->bindValue(":email", email);
        queryCreate->bindValue(":salt", *salt);
        queryCreate->bindValue(":password", *sha256);
        ok = manager->getDbService().exec(queryCreate);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::Register, ErrorType::Internal, QStringLiteral("")); }
    qDebug() << "[success]";
    return manager->getProtocol().createResponse(RequestType::Register, true);
}

QSharedPointer<IChatMsg> UserService::changePassword(quint32 userId, const QString & oldPassword, const QString & newPassword) const {
    qDebug() << "[UserService][changePassword] u: " << userId;
    if(userId <= 0){ return manager->getProtocol().createResponse(RequestType::ChangePassword, ErrorType::Custom, QStringLiteral("Requires active session")); }

    //Validate inputs
    if(newPassword.length() < 6){
        //Should already be handled by client -> Probably someone testing out the system, who doesn't need an error message
        return manager->getProtocol().createResponse(RequestType::ChangePassword, ErrorType::Custom, QStringLiteral("Invalid input"));
    }

    //Validate old Password
    QSharedPointer<QSqlQuery> query = manager->getDbService().prepare("SELECT salt, password FROM user WHERE id = :userid;");
    bool ok = false;
    if(!query.isNull()){
        query->bindValue(":userid", userId);
        ok = manager->getDbService().exec(query);
    }
    if(!ok || !query->next()){
        qDebug() << "Could not find user, who logged in";
        return manager->getProtocol().createResponse(RequestType::ChangePassword, ErrorType::Internal, QStringLiteral(""));
    }

    QString dbSalt = query->value(0).toString();
    QString dbPassword = query->value(1).toString();
    QSharedPointer<QString> oldSha256 = generatePassword(oldPassword, dbSalt);
    if(*oldSha256 != dbPassword){
        qDebug() << "old password incorrect";
        return manager->getProtocol().createResponse(RequestType::ChangePassword, ErrorType::Custom, QStringLiteral("Incorrect old password"));
    }

    //Generate and save new Password
    QSharedPointer<QString> salt = this->generateString(USERSERVICE_SALT_LENGTH);
    QSharedPointer<QString> newSha256 = generatePassword(newPassword, *salt);
    QSharedPointer<QSqlQuery> updateQuery = manager->getDbService().prepare("UPDATE user SET `password` = :newpassword, `salt` = :newsalt WHERE `id` = :userid;");
    ok = false;
    if(!updateQuery.isNull()){
        updateQuery->bindValue(":newpassword", *newSha256);
        updateQuery->bindValue(":newsalt", *salt);
        updateQuery->bindValue(":userid", userId);
        ok = manager->getDbService().exec(updateQuery);
    }
    if(!ok){ return manager->getProtocol().createResponse(RequestType::ChangePassword, ErrorType::Internal, QStringLiteral("")); }

    return manager->getProtocol().createResponse(RequestType::ChangePassword, true);
}
