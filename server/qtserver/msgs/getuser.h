#ifndef GETUSER_H
#define GETUSER_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class GetUser final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    quint32 userId;
public:
    explicit GetUser(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;
};

#endif // GETUSER_H
