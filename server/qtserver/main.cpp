#include <iostream>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include <QTextStream>
#include "jsonreader.h"
#include "server.h"

#ifdef QT_DEBUG
    #include "test/testmain.h"
#endif

int main(int argc, char *argv[])
{
    QTextStream cout(stdout);

#ifdef QT_DEBUG
    TestMain tests;
    tests.execute();
    cout << endl << endl;
#endif

    QCoreApplication a(argc, argv);
    //** Read Config **//
    {
        //Open file
        cout << QStringLiteral("Read configuration...\t\t");
        QFile settingFile(QStringLiteral("../settings.json"));
        if(!settingFile.open(QIODevice::ReadOnly)){ qFatal("Could not open settings file 'settings.json'"); }
        QJsonDocument settingDoc(QJsonDocument::fromJson(settingFile.readAll()));
        JsonReader reader(QSharedPointer<QJsonObject>(new QJsonObject(settingDoc.object())));
        cout << QStringLiteral("[success]") << endl;

        //Initialize Database Connection
        cout << QStringLiteral("Initializing database connection...\t");
        QSqlDatabase db = QSqlDatabase::addDatabase(*reader.readString(QStringLiteral("driver")));
        db.setHostName(*reader.readString(QStringLiteral("host")));
        db.setDatabaseName(*reader.readString(QStringLiteral("db")));
        db.setUserName(*reader.readString(QStringLiteral("user")));
        db.setPassword(*reader.readString(QStringLiteral("password")));
        bool ok = db.open();
        cout << (ok ? QStringLiteral("[success]") : QStringLiteral("[failed]")) << endl;
        if(!ok){ qFatal(db.lastError().text().toLatin1()); }

        //Initialize Websocket Server
        cout << QStringLiteral("Initializing websocket server...\t");
        Server *server = new Server(reader.readInt(QStringLiteral("ws-port")));
        cout << QStringLiteral("[success]") << endl;

        //Test lookup
        /*QSqlQuery query;
        ok = query.exec("SELECT username FROM user");
        if(!ok){ qFatal(db.lastError().text().toLatin1()); }
        while(query.next()){
            cout << query.value(0).toString() << endl;
        }*/

    }
    return a.exec();
}
