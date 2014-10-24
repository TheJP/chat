#ifndef GETCONVERSATIONS_H
#define GETCONVERSATIONS_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class GetConversations final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
public:
    explicit GetConversations(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // GETCONVERSATIONS_H
