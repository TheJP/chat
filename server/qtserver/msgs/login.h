#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QSharedPointer>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class Login final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    QSharedPointer<QString> username;
    QSharedPointer<QString> password;
public:
    explicit Login(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // LOGIN_H
