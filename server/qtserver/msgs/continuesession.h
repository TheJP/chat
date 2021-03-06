#ifndef CONTINUESESSION_H
#define CONTINUESESSION_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class ContinueSession final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    QSharedPointer<QString> sid;
public:
    explicit ContinueSession(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // CONTINUESESSION_H
