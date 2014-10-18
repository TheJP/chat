#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QCryptographicHash>
#include "../ichatmsg.h"

class UserService : public QObject
{
    Q_OBJECT
private:
    QString applicationSalt;
    char * letters;
public:
    explicit UserService(const QString & applicationSalt, QObject *parent = 0);
    ~UserService();
    QSharedPointer<IChatMsg> login(const QString & username, const QString & password) const;
signals:

public slots:

};

#endif // USERSERVICE_H
