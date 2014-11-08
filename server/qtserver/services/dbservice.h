#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSharedPointer>

class DbService : public QObject
{
    Q_OBJECT
public:
    explicit DbService(QObject *parent = 0);
    //Connects to the databse with the given parameters
    bool connect(const QString & driver,
                 const QString & hostname,
                 const QString & dbname,
                 const QString & user,
                 const QString & password);
    //Reconnects to the database (using the same parameters as the last call to connect)
    bool reconnect();
    //Prepares an QSqlQuery. Parameter can be binded to the resulting query instance
    //Returns a null pointer if the connection failed
    QSharedPointer<QSqlQuery> prepare(const QString & sql);
    //Execute a query which was created over prepare
    //Returns if the execution was successfull
    bool exec(QSharedPointer<QSqlQuery> query);
signals:

public slots:

};

#endif // DBSERVICE_H
