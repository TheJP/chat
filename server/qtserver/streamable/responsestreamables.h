#ifndef RESPONSECONVERSATIONS_H
#define RESPONSECONVERSATIONS_H

#include <QObject>
#include <QHash>
#include <QSharedPointer>
#include <QVector>
#include "response.h"
#include "../protocol.h"
#include "../istreamable.h"
#include "../services/servicemanager.h"

class ResponseStreamables final : public Response
{
    Q_OBJECT
private:
    QSharedPointer<QString> type;
    StreamableVector streamables;
public:
    explicit ResponseStreamables(const StreamableVector & streamables, const QSharedPointer<QString> & type, RequestType request, bool success, QObject *parent = 0);
    ~ResponseStreamables();
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
};

#endif // RESPONSECONVERSATIONS_H
