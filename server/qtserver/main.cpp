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
        cout << QStringLiteral("Read configuration...\t");
        QFile settingFile(QStringLiteral("../settings.json"));
        if(!settingFile.open(QIODevice::ReadOnly)){ qFatal("Could not open settings file 'settings.json'"); }
        QJsonDocument settingDoc(QJsonDocument::fromJson(settingFile.readAll()));
        JsonReader reader(QSharedPointer<QJsonObject>(new QJsonObject(settingDoc.object())));
        cout << QStringLiteral("[success]") << endl;

        //Initialize Database
        cout << QStringLiteral("Initializing database...\t");
        QSqlDatabase db = QSqlDatabase::addDatabase(*reader.readString(QStringLiteral("driver")));
        db.setHostName(*reader.readString(QStringLiteral("host")));
        db.setDatabaseName(*reader.readString(QStringLiteral("db")));
        db.setUserName(*reader.readString(QStringLiteral("user")));
        db.setPassword(*reader.readString(QStringLiteral("password")));
        bool ok = db.open();
        cout << (ok ? QStringLiteral("[success]") : QStringLiteral("[failed]")) << endl;
        if(!ok){ qFatal(db.lastError().text().toLatin1()); }
    }
    return a.exec();
    cout << "ende" << endl;
}
