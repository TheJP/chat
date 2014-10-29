#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QObject>
#include <QSharedPointer>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class SendMessage final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    quint32 conversationId;
    QSharedPointer<QString> message;
public:
    explicit SendMessage(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // SENDMESSAGE_H
