#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>
#include <QSharedPointer>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class Register final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    QSharedPointer<QString> username;
    QSharedPointer<QString> email;
    QSharedPointer<QString> password;
public:
    explicit Register(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // REGISTER_H
