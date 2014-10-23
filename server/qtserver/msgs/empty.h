#ifndef EMPTY_H
#define EMPTY_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class Empty final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
public:
    explicit Empty(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // EMPTY_H
