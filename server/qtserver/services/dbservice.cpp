#include "dbservice.h"

//TODO: remove
#include <QDebug>

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
    bool ok = result->prepare(sql);
    if(!ok){ qDebug() << result->lastError() << QStringLiteral("Trying reconnect"); }
    ok = ok || (this->reconnect() && result->prepare(sql));
    if(!ok){ qDebug() << result->lastError(); }
    return ok ? result : QSharedPointer<QSqlQuery>();
}

bool DbService::exec(QSharedPointer<QSqlQuery> query) const {
    bool ok = query->exec();
    if(!ok){ qDebug() << query->lastError() << QStringLiteral("Trying reconnect"); }
    ok = ok || (this->reconnect() && query->exec());
    if(!ok){ qDebug() << query->lastError(); }
    return ok;
}
