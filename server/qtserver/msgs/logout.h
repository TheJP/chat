#ifndef LOGOUT_H
#define LOGOUT_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class Logout : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
public:
    explicit Logout(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // LOGOUT_H
