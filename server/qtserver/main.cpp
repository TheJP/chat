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
#include <QSharedPointer>
#include <QObject>
#include "jsonreader.h"
#include "server.h"
#include "protocol.h"
#include "iformat.h"
#include "jsonformat.h"
#include "services/servicemanager.h"
#include "notificationsender.h"

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
        //Open Configuration File
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

        //** Dependency Injection **//

        //Initialize Server Protocol
        cout << QStringLiteral("Initializing server protocol...\t");
        QSharedPointer<Protocol> protocol(new Protocol());
        protocol->initDefault();
        cout << QStringLiteral("[success]") << endl;

        //Initialize Server Formats
        cout << QStringLiteral("Initializing server formats...\t");
        QSharedPointer<JsonFormat> format(new JsonFormat());
        cout << QStringLiteral("[success]") << endl;

        //Initialize Notification Sender
        cout << QStringLiteral("Initializing notification sender...\t");
        QSharedPointer<NotificationSender> notifier(new NotificationSender());
        cout << QStringLiteral("[success]") << endl;

        //Initialize Service Manager
        cout << QStringLiteral("Initializing service manager...\t");
        QSharedPointer<ServiceManager> manager(new ServiceManager(notifier));
        cout << QStringLiteral("[success]") << endl;

        //Initialize Websocket Server
        cout << QStringLiteral("Initializing websocket server...\t");
        Server * server = new Server(reader.readInt(QStringLiteral("ws-port")), protocol, format, manager);
        server->start();
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
