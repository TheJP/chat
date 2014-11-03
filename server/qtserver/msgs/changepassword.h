#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QObject>
#include <QSharedPointer>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class ChangePassword final : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    QSharedPointer<QString> oldPassword;
    QSharedPointer<QString> newPassword;
public:
    explicit ChangePassword(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;

signals:

public slots:

};

#endif // CHANGEPASSWORD_H
