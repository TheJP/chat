#ifndef NOTIFICATIONSENDER_H
#define NOTIFICATIONSENDER_H

#include <QObject>
#include <QList>
class IChatMsg; //Resolve cyclic includes

class NotificationSender : public QObject
{
    Q_OBJECT
public:
    explicit NotificationSender(QObject *parent = 0);

signals:
    void newNotification(IChatMsg & msg, const QList<int> & sessions) const;
public slots:

};

#endif // NOTIFICATIONSENDER_H
