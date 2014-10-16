#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include "userservice.h"

class ServiceManager : public QObject
{
    Q_OBJECT
private:
    UserService user;
public:
    explicit ServiceManager(QObject *parent = 0);
    const UserService & getUserService() const;
signals:

public slots:

};

#endif // SERVICEMANAGER_H
