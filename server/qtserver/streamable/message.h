#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "../istreamable.h"

class Message final : public QObject, public IStreamable
{
    Q_OBJECT
    Q_INTERFACES(IStreamable)
public:
    quint32 id;
    QSharedPointer<QString> message;
    int time;
    quint32 conversationId;
    quint32 userId;
    QSharedPointer<QString> username;
    explicit Message(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
};

#endif // MESSAGE_H
