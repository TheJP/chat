#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class Login : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
public:
    explicit Login(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    QSharedPointer<IChatMsg> create() override;
    QSharedPointer<IChatMsg> handle(ServiceManager manager) override;

signals:

public slots:

};

#endif // LOGIN_H
