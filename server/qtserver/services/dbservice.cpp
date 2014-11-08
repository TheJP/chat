#include "dbservice.h"

DbService::DbService(QObject *parent) :
    QObject(parent)
{
}

bool DbService::connect(const QString & driver,
                        const QString & hostname,
                        const QString & dbname,
                        const QString & user,
                        const QString & password) const {
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);
    db.setHostName(hostname);
    db.setDatabaseName(dbname);
    db.setUserName(user);
    db.setPassword(password);
    return db.open();
}

bool DbService::reconnect() const {
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    return db.open();
}

QSharedPointer<QSqlQuery> DbService::prepare(const QString & sql) const {
    QSharedPointer<QSqlQuery> result(new QSqlQuery());
    //Only execute reconnect if prepare fails
    bool ok = result->prepare(sql) || (this->reconnect() && result->prepare(sql));
    return ok ? result : QSharedPointer<QSqlQuery>();
}

bool DbService::exec(QSharedPointer<QSqlQuery> query) const {
    return query->exec() || (this->reconnect() && query->exec());
}
