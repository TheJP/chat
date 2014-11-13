#ifndef USER_H
#define USER_H

#include <QObject>
#include "../istreamable.h"

class User final : public QObject, public IStreamable
{
    Q_OBJECT
    Q_INTERFACES(IStreamable)
public:
    quint32 id;
    QSharedPointer<QString> username;
    QSharedPointer<QString> status;
    QSharedPointer<QString> description;
    explicit User(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
};

#endif // USER_H
