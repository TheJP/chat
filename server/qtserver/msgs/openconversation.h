#ifndef OPENCONVERSATION_H
#define OPENCONVERSATION_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class OpenConversation final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    quint32 conversationId;
public:
    explicit OpenConversation(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // OPENCONVERSATION_H
