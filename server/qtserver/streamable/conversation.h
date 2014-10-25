#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QObject>
#include "../istreamable.h"

class Conversation final : public QObject, public IStreamable
{
    Q_OBJECT
    Q_INTERFACES(IStreamable)
private:
public:
    quint32 id;
    QString title;
    QString topic;
    QString description;
    bool root;
    quint32 parent_id;
    explicit Conversation(QObject *parent = 0);
    void read(IKeyValueReader & stream) override;
    void write(IKeyValueWriter & stream) override;
signals:

public slots:

};

#endif // CONVERSATION_H
