#ifndef RESPONSE_H
#define RESPONSE_H

#define KEY_REQUEST_TYPE QStringLiteral("r")
#define KEY_SUCCESS QStringLiteral("s")

#include <QObject>
#include <QHash>
#include "../protocol.h"
#include "../ichatmsg.h"
#include "../services/servicemanager.h"

class Response : public QObject, public IChatMsg
{
    Q_OBJECT
    Q_INTERFACES(IChatMsg)
private:
    RequestType request;
    bool success;
    ErrorType error;
    QString errorText;
public:
    explicit Response(RequestType request, bool success, QObject *parent = 0);
    explicit Response(RequestType request, ErrorType error, const QString & errorText, QObject *parent = 0);
    virtual void read(IKeyValueReader & stream) override;
    virtual void write(IKeyValueWriter & stream) override;
    virtual QSharedPointer<IChatMsg> create() override;
    virtual QSharedPointer<IChatMsg> handle(const ServiceManager & manager) override;
signals:

public slots:

};

#endif // RESPONSE_H
