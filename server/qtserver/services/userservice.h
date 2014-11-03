#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include "../ichatmsg.h"

#define USERSERVICE_COUNT_LETTERS 36
#define USERSERVICE_SID_LENGTH 256
#define USERSERVICE_SALT_LENGTH 64
#define USERSERVICE_MAX_GENERATE_LENGTH 256

class UserService : public QObject
{
    Q_OBJECT
private:
    ServiceManager * manager;
    QString applicationSalt;
    char * letters;
    QSharedPointer<QString> generateString(int length) const;
    QSharedPointer<QString> generatePassword(const QString & password, const QString & salt) const;
public:
    explicit UserService(ServiceManager * manager, const QString & applicationSalt, QObject *parent = 0);
    ~UserService();
    QSharedPointer<IChatMsg> login(const QString & username, const QString & password) const;
    QSharedPointer<IChatMsg> logout(const QString & sid) const;
    QSharedPointer<IChatMsg> continueSession(const QString & sid) const;
    QSharedPointer<IChatMsg> createUser(const QString & username, const QString & email, const QString & password) const;
    QSharedPointer<IChatMsg> changePassword(quint32 userId, const QString & oldPassword, const QString & newPassword) const;
signals:

public slots:

};

#endif // USERSERVICE_H
