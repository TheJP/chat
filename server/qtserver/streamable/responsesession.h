#ifndef RESPONSESESSION_H
#define RESPONSESESSION_H

#include <QObject>
#include <QHash>
#include <QSharedPointer>
#include "response.h"
#include "../protocol.h"
#include "../services/servicemanager.h"

class ResponseSession final : public Response
{
    Q_OBJECT
private:
    quint32 numSid;
    QSharedPointer<QString> sid;
    quint32 userId;
    QSharedPointer<QString> username;
public:
    explicit ResponseSession(quint32 numSid, const QSharedPointer<QString> & sid, quint32 userId, const QSharedPointer<QString> & username, RequestType request, bool success, QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
    quint32 getNumSid() const;
    quint32 getUserId() const;
signals:

public slots:

};

#endif // RESPONSESESSION_H
