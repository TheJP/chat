#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include <QSharedPointer>
#include "../ichatmsg.h"

class UserService : public QObject
{
    Q_OBJECT
public:
    explicit UserService(QObject *parent = 0);
    QSharedPointer<IChatMsg> login(const QString & username, const QString & password) const;
signals:

public slots:

};

#endif // USERSERVICE_H
