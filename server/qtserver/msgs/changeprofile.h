#ifndef CHANGEPROFILE_H
#define CHANGEPROFILE_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class ChangeProfile final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    QSharedPointer<QString> status;
    QSharedPointer<QString> description;
public:
    explicit ChangeProfile(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;
};

#endif // CHANGEPROFILE_H
